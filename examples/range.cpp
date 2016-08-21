
#include <lars/generator.h>
#include <iostream>

using namespace lars;
using namespace std;

Generator<int> range(int max){
  return Generator<int>([=](Yield<int> &yield){
    for(int i = 0;i<max;++i) yield(i);
  });
}

int main(){
  for(int i:range(10)) std::cout << i << std::endl;
}


