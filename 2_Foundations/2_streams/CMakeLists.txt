cmake_minimum_required(VERSION 3.7)

project(streams)

# set the use of C++17 globally as all examples require it
set(CMAKE_CXX_STANDARD 17)

find_package(vsg REQUIRED)

add_executable(streams streams.cpp)

target_link_libraries(streams vsg::vsg)
