cmake_minimum_required(VERSION 3.7)

project(observer_ptr)

find_package(vsg REQUIRED)

add_executable(observer_ptr observer_ptr.cpp)

target_link_libraries(observer_ptr vsg::vsg)
