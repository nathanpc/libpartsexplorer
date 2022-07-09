### CMakeList.txt
### CMake definitions to build the PartsExplorer test application.
###
### Author: Nathan Campos <nathan@innoveworkshop.com>

# Setup the project.
project(petest VERSION 1.0.0 LANGUAGES C)
set(PROJECT_LINK_LIBS libpartsexplorer.a)

# Setup the files we are going to use.
file(GLOB SOURCES "*.c")
include_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_BINARY_DIR}/libpartsexplorer)

# Build our test binary.
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})

# Configure the installation.
install(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin)
