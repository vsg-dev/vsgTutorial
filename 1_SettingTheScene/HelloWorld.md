---
layout: page
title: Hello World
permalink: /SettingTheScene/HelloWorld
---

To download the tutorial exercises, clone the vsgTutorial repository.  It contains both the book contents and the exercises:
~~~ sh
cd ${PROJECT_DIR}
git clone https://github.com/vsg-dev/vsgTutorial.git
~~~

To build the hello world exercise change into the exercise directory, and use the following CMake script to build a standalone application:

~~~ cmake
{% include_relative 01_hello_world/CMakeLists.txt %}
~~~

To build the application change into source directory, run CMake then make:

~~~ sh
cd vsgTutorial/1_SettingTheScene/01_hello_world
cmake .
make 
~~~

The hello world exercise is just a single main() function that has three sections to it:

1. create the scene graph
1. create and setup the viewer to render the scene graph
1. execute the frame loop which does the handling of GUI events and rendering.

~~~ cpp
{% include_relative 01_hello_world/hello_world.cpp %}
~~~

To run the application:

~~~ sh
./helloworld
~~~

---

Prev: [Building VulkanSceneGraph Software](BuildingVulkanSceneGraph.md) | Next: [Next Chapter : Foundations](../2_Foundations/index.md)
