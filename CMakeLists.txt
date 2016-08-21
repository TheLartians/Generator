cmake_minimum_required(VERSION 3.1)

set(headers "${CMAKE_CURRENT_SOURCE_DIR}/include/lars/generator.h")

if(lars_headers)
  list(APPEND lars_headers ${headers})
  list(APPEND lars_include_dirs "${CMAKE_CURRENT_SOURCE_DIR}/include")
else(lars_headers)

  include_directories("include")
  set(CMAKE_CXX_STANDARD 11)

  file( GLOB example_sources examples/*.cpp )
  foreach( examplesourcefile ${example_sources} )
    get_filename_component(filename ${examplesourcefile} NAME)
    string( REPLACE ".cpp" "" examplename ${filename} )
    add_executable( ${examplename} ${examplesourcefile} ${headers})
  endforeach( examplesourcefile ${test_sources} )

endif(lars_headers)



