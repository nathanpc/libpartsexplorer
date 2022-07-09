### CMakeList.txt
### CMake definitions for the PartsExplorer library project.
###
### Author: Nathan Campos <nathan@innoveworkshop.com>

# Determine the minimum CMake version.
cmake_minimum_required(VERSION 3.0)

# Setup the project.
project(libpartsexplorer VERSION 0.1.0 LANGUAGES C)
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -pedantic)

# If we are in Debug mode, make install will output to the build directory. 
if(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Build Type: Debug")
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/build)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

# Compile the static library.
add_subdirectory(src ${CMAKE_BINARY_DIR}/libpartsexplorer)
add_subdirectory(test ${CMAKE_BINARY_DIR}/petest)
