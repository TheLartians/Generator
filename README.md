[![Build Status](https://travis-ci.com/TheLartians/Generator.svg?branch=master)](https://travis-ci.com/TheLartians/Generator)

# lars::Generator

A generator class emulating yield functionality through `std::thread` for simple iterator creation.

# Example

The code below shows how to create a python-style range iterator.

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

Installation and usage
----------------------
With [CPM](https://github.com/TheLartians/CPM), lars::Generator can be added to your project by adding the following to your projects' `CMakeLists.txt`.

```cmake
CPMAddPackage(
  NAME LarsGenerator
  VERSION 0.1
  GIT_REPOSITORY https://github.com/TheLartians/Generator.git
)

target_link_libraries(myProject LarsGenerator)
```

Alternatively, download the repository include it via `add_subdirectory`. Installing lars::Generator will make it findable in CMake's `find_package`.
