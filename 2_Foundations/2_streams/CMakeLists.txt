cmake_minimum_required(VERSION 3.7)

project(streams)

find_package(vsg REQUIRED)

add_executable(streams streams.cpp)

target_link_libraries(streams vsg::vsg)
