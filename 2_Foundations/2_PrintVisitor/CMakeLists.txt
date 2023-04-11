cmake_minimum_required(VERSION 3.7)

project(PrintVisitor)

find_package(vsg REQUIRED)

add_executable(PrintVisitor PrintVisitor.cpp)

target_link_libraries(PrintVisitor vsg::vsg)
