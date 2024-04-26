cmake_minimum_required(VERSION 3.7)

project(observer_ptr)

# set the use of C++17 globally as all examples require it
set(CMAKE_CXX_STANDARD 17)

find_package(vsg REQUIRED)

add_executable(observer_ptr observer_ptr.cpp)

target_link_libraries(observer_ptr vsg::vsg)
