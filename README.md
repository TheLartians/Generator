[![Build Status](https://travis-ci.com/TheLartians/Generator.svg?branch=master)](https://travis-ci.com/TheLartians/Generator)

# Generator
A python-style generator class emulating yield functionality for simple and memory-efficient iterator creation.

# Example

```cpp
#include <lars/generator.h>
#include <iostream>

lars::Generator<int> range(int max){
  return lars::Generator<int>([=](lars::Yield<int> &yield){
    for(int i = 0;i<max;++i) yield(i);
  });
}

int main(){
  for(int i:range(10)) std::cout << i << std::endl;
}
```
