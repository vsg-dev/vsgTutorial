---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---

**CURRENTLY IN DEVELOPMENT : Early stage of development so expect missing sections and rough and ready state.**

The goal of this tutorial is to teach developers how to use the [VulkanSceneGraph](https://github.com/vsg-dev/VulkanSceneGraph) effectively in their graphics and compute applications. The tutorial assumes developers have prior knowledge of using CMake and C++ to build and write applications.  Knowledge of scene graphs, real-time graphics and Vulkan are not assumed, though teaching real-time graphics and Vulkan at depth is beyond the scope of this tutorial, links to 3rd party resources for further learnning will be provided.

Each chapter of the tutorial is coupled with exercises so that developers can learn about each topic then test out what they have learned. The topics covered are:

1. [Setting The Scene](SettingTheScene.md)  
Introduction to low and high level APIs, the software design and performance preciples used in development of the VulkanSceneGraph, the ecosystem build up up around the project, high level features and conventions you'll get with the core VulkanSceneGraph library and wraps up with how to build the software and run the first exercise - a scene graph take on hello world.

2. Fundations  
This chaper covers the foundational base classes, memory management, maths and IO support that the rest of the scene graph functionality is built upon.

3. Scene Graph  
Nodes - internal nodes of the scene graph,  Geometry - meshes, State - shaders, textures, uniforms.

4. Application  
Viewer - creating application viewer, Utilities - operating on the scene graph, Threading - different ways of threading.

Chapter 5: Developing Skills  
Trouble Shooting - debugging VulkanSceneGraph applications, Optimizaton - how to improve performance & low power consumption.
