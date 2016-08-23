
#include <lars/generator.h>
#include <iostream>

using namespace lars;
using namespace std;


int main(){

  auto fibonacci_numbers = Generator<long>([=](Yield<long> &yield){
    long a = 0, b = 1;
    yield(a);
    yield(b);
    while(true){
      long t = a + b;
      yield(t);
      a = b;
      b = t;
    }
  });
  
  for(auto i:fibonacci_numbers){
     if(i > 1000000) break;
     std::cout << i << std::endl;
  }
  
}

