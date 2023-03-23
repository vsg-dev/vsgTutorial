---
layout: page
title: Building VulkanSceneGraph Projects and Tutorial Exercises
permalink: /introduction/BuildingVulkanSceneGraph
---

All VulkanSceneGraph projects, including the vsgTutorial exercises, are written in C++17 and using CMake as a cross platform build systen. To aid integration of the VulkanSceneGraph projects with other software CMake config files are installed along with headers and libraries.  CMake config files provide details of the libaries, header locations and any compile definitions that are required when building software that use VulkanSceneGraph libraries and helps avoid issues when working across different platforms and with differences in static and dynamic library builds.


{% include_relative 01_hello_world/CMakeLists.txt %}

--

~~
{% include_relative 01_hello_world/CMakeLists.txt %}
~~

---

~~
find_package(vsg 1.0.3 REQUIRED)
find_package(vsgXchange 1.0.2 REQUIRED)

add_executable(hello_world hello_world.cpp)

target_link_libraries(hello_world vsg::vsg vsgXchange::vsgXchange)
~~


Prev: [Introduction to VulkanSceneGraph Project](VulkanSceneGraph.md) | Next : [Foundations](../foundations.md)
