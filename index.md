---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---

The goal of this tutorial is to teach developers how to use the VulkanSceneGraph effectively in their graphical and compute applications. The tutorial assumes developers have prior knowledge of using CMake and C++ to build and write applications.  Knowledge of scene graphs, real-time graphics and Vulkan is not assumed, though teaching real-time graphics and Vulkan at depth is beyond the scope of this tutorial, links to 3rd party resources for further learnning will be provided.

The tutorial is composed of series of presententations that are coupled with exercises so that developers can learn about each topic then test out what they have learned. The topics covered are:

Introduction:
1. [Low level APIs](introduction/LowLevelAPIs.md)
1. [High Level APIs](introduction/HighLevelAPIs.md)
1. [Vulkan](introduction/Vulkan.md)
1. [VulkanSceneGraph](introduction/VulkanSceneGraph.md)
1. [Building the VulkanScenegraph projects and vsgTutorial exercises](introduction/BuildingVulkanSceneGraph.md)

Fundations:
4. Core classes - smart pointers, Objects and Allocators
5. Vector maths - GLSL style vectors, matrices
6. IO - loading/saving images and nodes

Scene Graph:
7. Nodes - internal nodes of the scene graph
8. Geometry - meshes
9. State - shaders, textures, uniforms

Application:
10. Viewer - creating application viewer
11. Utilizties - operating on the scene graph
12. Threading - different ways of threading

Developing Skills:
13. Trouble Shooting - debugging VulkanSceneGraph applications
14. Optimizaton - how to improve performance & low power consumption
