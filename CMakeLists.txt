cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# ---- Project ----

project(LarsGenerator 
  VERSION 0.1
  LANGUAGES CXX
)
# ---- Configuration variables ----

option(LarsGenerator_ENABLE_TESTS "Enable LarsGenerator tests" OFF)
option(LarsGenerator_BUILD_EXAMPLES "Build LarsGenerator examples" OFF)

# ---- Include guards ----

if(TARGET LarsGenerator)
  return()
endif()

if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# ---- Header target ----

FILE(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/include/lars/*.h")
add_library(LarsGenerator-headers EXCLUDE_FROM_ALL ${headers})
SET_TARGET_PROPERTIES(LarsGenerator-headers PROPERTIES LINKER_LANGUAGE CXX)

# ---- Create library ----

add_library(LarsGenerator INTERFACE)
target_link_libraries(LarsGenerator INTERFACE pthread)

target_include_directories(LarsGenerator
  INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/LarsGeneratorConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# ---- Install ----

install(
  TARGETS LarsGenerator
  EXPORT LarsGeneratorTargets
  LIBRARY DESTINATION lib COMPONENT Runtime
  ARCHIVE DESTINATION lib COMPONENT Development
  RUNTIME DESTINATION bin COMPONENT Runtime
  PUBLIC_HEADER DESTINATION include COMPONENT Development
  BUNDLE DESTINATION bin COMPONENT Runtime
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/LarsGeneratorConfig.cmake.in"
  "${PROJECT_BINARY_DIR}/LarsGeneratorConfig.cmake"
  INSTALL_DESTINATION lib/cmake/LarsGenerator
)

install(
  EXPORT LarsGeneratorTargets 
  DESTINATION lib/cmake/LarsGenerator
)

install(
  FILES 
    "${PROJECT_BINARY_DIR}/LarsGeneratorConfigVersion.cmake"
    "${PROJECT_BINARY_DIR}/LarsGeneratorConfig.cmake"
  DESTINATION 
    lib/cmake/LarsGenerator
)

install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/include/
  DESTINATION include
)

# ---- Tests and examples ----

if (${LarsGenerator_BUILD_EXAMPLES})
  add_subdirectory(examples)  
endif()

if (${LarsGenerator_ENABLE_TESTS})
  ENABLE_TESTING()  
  add_subdirectory(tests)  
endif()

