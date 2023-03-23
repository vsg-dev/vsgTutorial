---
layout: page
title: VulkanSceneGraph Library
permalink: /introduction/VulkanSceneGraphLibrary
---

The [VulkanSceneGraph library](https://github.com/vsg-dev/VulkanSceneGraph/) provides the features that will be common to all applications - creating a viewer, windows, scene graph, reading/writing data, creating Vulkan objects and recording Vulkan commands, synchronizing with Vulkan processes and CPU threads, 3d vector maths and common utilities like computing bounds and intersection test and shader composition and cmpilation. 

All the VulkanSceneGraph follow the same structure - public headers can be found in include/ directories and the implementation can be found in the src/ direcotories. This pattern is used to make it clear to end users what part of they will interface with, and as clear demarcation to library developers & contributors that interfaces and implementations both have clear and distinct roles. When installing the software it'll only the files in the include directories and any built libraries + cmake config files that will be installed.

The [vsg library headers](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg) are grouped in the following [include/vsg](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/) subdirectories:

Foundational class directories:
* [core](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core) - base classes, smart pointer, data continers, allocators and visitor base classes
* [maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths) - GLSL style maths classes, similar to glm
* [io](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io) - serialization and built-in reader/writers.

Scene graph class directories:
* [commands](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/commands) - scene graph nodes for Vulkan Commands
* [state](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/state) - scene graph objects for setting Vulkan state.
* [nodes](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/) - scene graph nodes like groups, swtiches & transforms
* [text](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/text) - text scene graph nodes
* [meshshaders](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/meshshaders) - Khronos Mesh Shader support
* [raytracing](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/raytracing) - Khronos Ray Tracing support

Application class directories:
* [vk](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/vk) - high level Vulkan integration such vkInstance/vkDevice etc.
* [app](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/app) - application level Vulkan classes
* [threading](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/threading) - threading classes and helper functions
* [platform](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/platform) - platform specific Windowing support
* [ui](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/ui) - user interface classes such as mouse and keyboard events
* [utils](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/utils) - collection of utilities such intersections through to shader composition and compilation.

---

 Prev: [VulkanSceneGraph Project](VulkanSceneGraphProject.md)| Next: [Building VulkanSceneGraph projeects and exercises](BuildingVulkanSceneGraph.md)
