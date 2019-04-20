#include <catch2/catch.hpp>
#include <iterator>

#include <lars/generator.h>

TEST_CASE("Range Generator") {

  using namespace lars;

  auto range = [](auto max){
    using T = decltype(max);
    return Generator<T>([=](Yield<T> &yield){
      for(T i = 0;i<max;++i) yield(i);
    });
  };

  std::vector<int> v;
  for (auto i: range(10)) {
    v.push_back(i);
  }

  REQUIRE(v.size() == 10);
  
  for (int i=0; i<10; ++i) {
    REQUIRE(v[i] == i);
  }

}

TEST_CASE("Fibonacci Generator") {
  using namespace lars;
  using Number = unsigned long long;

  auto fibonacci_numbers = Generator<Number>([=](Yield<Number> &yield){
    Number a = 0, b = 1;
    yield(a);
    yield(b);
    while(true){
      Number t = a + b;
      yield(t);
      a = b;
      b = t;
    }
  });

  auto it = fibonacci_numbers.begin();
  
  std::advance(it, 55);
  REQUIRE((*it) == 139583862445ll);
}


