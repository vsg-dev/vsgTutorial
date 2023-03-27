---
layout: page
title: Hello World
permalink: /SettingTheScene/HelloWorld
---

To download the tutorial exercises clone the vsgTutorial repository, this contains both the book contents and the exercises:
~~~ sh
cd ${PROJECT_DIR}
git clone https://github.com/vsg-dev/vsgTutorial.git
~~~

To build the hello world exercise we change in the exercise directory, we use the follow cmake script to build a stand alone application:

~~~ cmake
{% include_relative 01_hello_world/CMakeLists.txt %}
~~~

To build the application we change into source diretory, run cmake then make:

~~~ sh
cd vsgTutorial/1_SettingTheScene/01_hello_world
cmake .
make 
~~~

To run the application:

~~~ sh
./helloworld
~~~

The hellow world exercise is just single main function that has three sections to it, first we create the scene graph, second create and setup the viewer to render the scene graph and the final section executes the frame loop which does the handling of GUI events and rendering.
<!--
Load the scene graph:
~~~ cpp
{% include includelines filename='../1_SettingTheScene/01_hello_world/hello_world.cpp' start=1 count=25 %}
~~~
-->
Full code:
~~~ cpp
{% include_relative 01_hello_world/hello_world.cpp %}
~~~

---

Prev: [Building VulkanSceneGraph Software](BuildingVulkanSceneGraph.md) | Next : [Foundations](../2_Foundations/index.md)
