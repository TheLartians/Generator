#pragma once

#include <thread>
#include <future>
#include <memory>

namespace lars{
  
  template <class T> class Generator;
  
  template <class T> class Yield{

    enum State{ WAITING,READY,TERMINATED,FINISHED } state = WAITING;

    friend Generator<T>;
    std::promise<T> promise;
    std::mutex mutex;
    std::condition_variable ready_wait;
    
    struct FinishedException:public std::exception{ };
    struct TerminatedException:public std::exception{ };
   
    void terminate(){
      if(state != FINISHED){
        state = TERMINATED;
        ready_wait.notify_one();
      }
    }
    
    void finish(){
      if(state == TERMINATED) return;
      std::unique_lock<std::mutex> lock(mutex);
      if(state == WAITING) ready_wait.wait(lock);
      state = FINISHED;
      throw FinishedException();
    }
    
    template <class E> void set_exception(E e){
      std::unique_lock<std::mutex> lock(mutex);
      if(state == WAITING) ready_wait.wait(lock);
      promise.set_exception(e);
    }

    Yield(){ }
    
  public:
    void operator()(const T &value){
      std::unique_lock<std::mutex> lock(mutex);
      if(state == WAITING) ready_wait.wait(lock);
      if(state == TERMINATED) throw TerminatedException();
      promise.set_value(value);
      state = WAITING;
    }
    
    std::future<T> get_future(){
      promise = std::promise<T>();
      std::unique_lock<std::mutex> lock(mutex);
      ready_wait.notify_one();
      state = READY;
      return promise.get_future();
    }
    
  };
  
  template <class T> class Generator{
    std::function<void(Yield<T> &)> generator_function;
    
  public:
    
    class const_iterator{
      friend Generator;
      
      struct Data{
        Yield<T> yield;
        T current_value;
        std::thread thread;
        ~Data(){ yield.terminate(); thread.join(); }
      };
      
      std::unique_ptr<Data> data;
    public:
      
      const T &operator*(){ return data->current_value; }
      
      void operator++(){
        try{
          data->current_value = data->yield.get_future().get();
        }
        catch(typename Yield<T>::FinishedException){
          data.reset();
        }
      }
      
      bool operator!=(const const_iterator &other){ return data != other.data; }
    };
    
    Generator(const std::function<void(Yield<T> &)> &gf):generator_function(gf){ }
    
    const_iterator begin()const{
      const_iterator it;
      it.data.reset(new typename const_iterator::Data);
      auto data = it.data.get();
      
      data->thread = std::thread([this,data](){
        try{
          generator_function(data->yield);
          data->yield.finish();
        }
        catch(const typename Yield<T>::TerminatedException &){
          
        }
        catch(...){
          data->yield.set_exception(std::current_exception());
        }
      });
      
      ++it;
      
      return it;
    }
    
    const_iterator end()const{
      return const_iterator();
    }
    
  };
  
}

