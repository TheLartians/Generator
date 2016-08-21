
#include "../generator.h"
#include <iostream>

using namespace lars;
using namespace std;

Generator<int> fibonacci(int n){
  return Generator<int>([=](Yield<int> &yield){
    int a = 0, b = 1;
    for (int i=0;i<n;i++){
       int t = a + b;
       yield(t);
       a = b;
       b = t;
    }
  });
}

int main(){
  for(int i:fibonacci(10)) std::cout << i << std::endl;
}


