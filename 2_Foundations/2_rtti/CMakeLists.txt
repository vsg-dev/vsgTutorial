cmake_minimum_required(VERSION 3.7)

project(rtti)

# set the use of C++17 globally as all examples require it
set(CMAKE_CXX_STANDARD 17)

find_package(vsg REQUIRED)

add_executable(rtti rtti.cpp)

target_link_libraries(rtti vsg::vsg)
