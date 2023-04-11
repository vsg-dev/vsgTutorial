cmake_minimum_required(VERSION 3.7)

project(rtti)

find_package(vsg REQUIRED)

add_executable(rtti rtti.cpp)

target_link_libraries(rtti vsg::vsg)
