---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---

**CURRENTLY IN DEVELOPMENT: expect missing sections and rough and ready state.**

The goal of this tutorial is to teach developers how to use the [VulkanSceneGraph](https://github.com/vsg-dev/VulkanSceneGraph) effectively in their graphics and compute applications. The tutorial assumes developers have prior knowledge of using CMake and C++ to build and write applications.  Knowledge of scene graphs, real-time graphics and Vulkan are not assumed, though teaching real-time graphics and Vulkan at depth is beyond the scope of this tutorial, links to 3rd party resources for further learnning will be provided.

Each chapter of the tutorial is coupled with exercises so that developers can learn about each topic then test out what they have learned. The topics covered are:

1. [Setting The Scene](1_SettingTheScene/index.md) **First Draft**  
We introduce you to world of scene graphs with a brief tour of low and high level APIs from IrisGL & Inventor to Vulkan & VulkanSceneGraph. The chapter then turns to the software design and performance principles used development of the VulkanSceneGraph, the ecosystem building up around the project, high level features and conventions you'll get with the core VulkanSceneGraph library and wraps up with how to build the software and run the first exercise - a scene graph take on hello world.

2. [Fundations](2_Foundations/index.md) **To be written**  
This chapter covers the foundational base classes, memory management, maths and IO support that the rest of the scene graph functionality is built upon.

3. [Scene Graph](3_SceneGraph/index.md) **To be written**  
This chapter introduces the scene graph classes - the internal nodes through the geometry and state leaves.

4. [Application](4_Application/index.md) **To be written**  
This chapter focuses on application level classes - the viewer, windows, views, cameras, event handling, rendering loop, event handling and threading.

5. [Developing Skills](5_DevelopingSkills/index.md) **To be written**  
Final chapter wraps up with guidance on trouble shooting and debugging VulkanSceneGraph applications, through to how to improve performance & low power consumption.
