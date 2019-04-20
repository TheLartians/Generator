cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
include(FetchContent)

# ---- Project ----

project(LarsGeneratorTests CXX)

# ---- Requires ----

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  find_package(LarsGenerator REQUIRED)
endif()

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.5.0
)

FetchContent_MakeAvailable(Catch2)

# ---- Create binary ----

file(GLOB tests_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(lars-generator-tests ${tests_sources})
target_link_libraries(lars-generator-tests LarsGenerator Catch2)
set_target_properties(lars-generator-tests PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror")

# ---- Add tests ----

ENABLE_TESTING() 
ADD_TEST(lars-generator-tests lars-generator-tests)

