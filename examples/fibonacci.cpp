
#include <lars/generator.h>
#include <iostream>

using namespace lars;
using namespace std;

Generator<int> fibonacci(){
  return Generator<int>([=](Yield<int> &yield){
    int a = 0, b = 1;
    for(int i=0;;i++){
       int t = a + b;
       yield(t);
       a = b;
       b = t;
    }
  });
}

int main(){
  for(int i:fibonacci()){
     if(i > 1000) break;
     std::cout << i << std::endl;
  }
}


