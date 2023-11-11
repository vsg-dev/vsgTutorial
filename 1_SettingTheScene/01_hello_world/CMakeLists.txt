cmake_minimum_required(VERSION 3.7)

project(hello_world)

# set the use of C++17 globally as all examples require it
set(CMAKE_CXX_STANDARD 17)

find_package(vsg REQUIRED)
find_package(vsgXchange REQUIRED)

add_executable(hello_world hello_world.cpp)

target_link_libraries(hello_world vsg::vsg vsgXchange::vsgXchange)
