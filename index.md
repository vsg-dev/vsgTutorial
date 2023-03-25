---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---

**CURRENTLY IN DEVELOPMENT : Early stage of development so expect missing sections and rough and ready state.**

The goal of this tutorial is to teach developers how to use the [VulkanSceneGraph](https://github.com/vsg-dev/VulkanSceneGraph) effectively in their graphical and compute applications. The tutorial assumes developers have prior knowledge of using CMake and C++ to build and write applications.  Knowledge of scene graphs, real-time graphics and Vulkan is not assumed, though teaching real-time graphics and Vulkan at depth is beyond the scope of this tutorial, links to 3rd party resources for further learnning will be provided.

The tutorial is composed of series of presententations that are coupled with exercises so that developers can learn about each topic then test out what they have learned. The topics covered are:

Introduction:
1. [Low level APIs](introduction/LowLevelAPIs.md)
1. [Vulkan](introduction/Vulkan.md)
1. [High Level APIs](introduction/HighLevelAPIs.md)
1. [Development Principles](introduction/DevelopmentPrinciples.md)
1. [Performance Principles](introduction/PerformancePrinciples.md)
1. [VulkanSceneGraph Ecosystem](introduction/Ecosystem.md)
1. [VulkanSceneGraph Library](introduction/VulkanSceneGraphLibrary.md)
1. [Building the VulkanScenegraph projects and vsgTutorial exercises](introduction/BuildingVulkanSceneGraph.md)

Fundations:
1. Core classes - smart pointers, Objects and Allocators
1. Vector maths - GLSL style vectors, matrices
1. IO - loading/saving images and nodes

Scene Graph:
1. Nodes - internal nodes of the scene graph
1. Geometry - meshes
1. State - shaders, textures, uniforms

Application:
1. Viewer - creating application viewer
1. Utilities - operating on the scene graph
1. Threading - different ways of threading

Developing Skills:
1. Trouble Shooting - debugging VulkanSceneGraph applications
1. Optimizaton - how to improve performance & low power consumption
