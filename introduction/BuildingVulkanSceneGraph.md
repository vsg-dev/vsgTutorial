---
layout: page
title: Building VulkanSceneGraph software
permalink: /introduction/BuildingVulkanSceneGraph
---

To conclude this Introduction section we'll look at building the VulkanSceneGraph projects and minimal stand alone **hello world** application.

All VulkanSceneGraph projects, including the vsgTutorial exercises, are written in C++17 and using CMake as a cross platform build systen. To aid integration of the VulkanSceneGraph projects with other software CMake config files are installed along with headers and libraries.  CMake config files provide details of the libaries, header locations and any compile definitions that are required when building software that use VulkanSceneGraph libraries and helps avoid issues when working across different platforms and with differences in static and dynamic library builds.

The use of CMake config files really simplifies the inclusion of VulkanSceneGraph project, the hello world [CMakeLists.txt](01_hello_world/CMakeLists.txt) is less than 10 lines!

~~~ cmake
{% include_relative 01_hello_world/CMakeLists.txt %}
~~~

---



Prev: [Introduction to VulkanSceneGraph Project](VulkanSceneGraph.md) | Next : [Foundations](../foundations.md)
