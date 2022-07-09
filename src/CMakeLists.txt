### CMakeList.txt
### CMake definitions to build the PartsExplorer static library.
###
### Author: Nathan Campos <nathan@innoveworkshop.com>

# Setup the project.
project(partsexplorer VERSION 0.1.0 LANGUAGES C)

# Setup the files we are going to use.
file(GLOB SOURCES "*.c" "../lib/microtar/src/*.c")
file(GLOB HEADERS "*.h" "../lib/microtar/src/*.h")
include_directories(${CMAKE_SOURCE_DIR}/lib/cvector
  ${CMAKE_SOURCE_DIR}/lib/microtar/src)

# Build our static library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Set properties.
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")

# Configure the installation.
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
  INCLUDES DESTINATION include/${PROJECT_NAME})
