cmake_minimum_required(VERSION 3.7)

project(vsgTutorial)

# build all examples into the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(01_introduction/exercises)
