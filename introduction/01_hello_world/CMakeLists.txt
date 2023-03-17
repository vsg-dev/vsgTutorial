cmake_minimum_required(VERSION 3.7)

project(hello_world)

find_package(vsg 1.0.3 REQUIRED)
find_package(vsgXchange 1.0.2 REQUIRED)

add_executable(hello_world hello_world.cpp)

target_link_libraries(hello_world vsg::vsg vsgXchange::vsgXchange)
