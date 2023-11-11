cmake_minimum_required(VERSION 3.7)

project(PrintVisitor)

# set the use of C++17 globally as all examples require it
set(CMAKE_CXX_STANDARD 17)

find_package(vsg REQUIRED)

add_executable(PrintVisitor PrintVisitor.cpp)

target_link_libraries(PrintVisitor vsg::vsg)
