cmake_minimum_required(VERSION 3.7)

project(serialization)

find_package(vsg REQUIRED)

add_executable(serialization serialization.cpp)

target_link_libraries(serialization vsg::vsg)
