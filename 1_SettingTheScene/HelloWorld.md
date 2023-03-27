---
layout: page
title: Hello World
permalink: /SettingTheScene/HelloWorld
---

To build the hello world exercise:

~~~ sh
cd vsgTutorial/1_SettingTheScene/01_hello_world
cmake .
make 
~~~

To run the application:

~~~ sh
./helloworld
~~~

The source code of hello world:

~~~ cpp
{% include_relative 01_hello_world/hello_world.cpp %}
~~~

---

Prev: [Building VulkanSceneGraph Software](BuildingVulkanSceneGraph.md) | Next : [Foundations](../2_Foundations/index.md))
