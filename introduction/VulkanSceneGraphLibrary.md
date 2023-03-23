---
layout: page
title: VulkanSceneGraph Library
permalink: /introduction/VulkanSceneGraphLibrary
---

## Design and Development Reports

During the initial development phase the follow documents and reports were written which provide a insight into design and implementation decisions:

* Design : [Design Principles & Philosophy](docs/Design/DesignPrinciplesAndPhilosophy.md)
* Design : [High Level Design Decisions](docs/Design/HighLevelDesignDecisions.md)
* Exploration Phase : [3rd Party Resources](docs/ExplorationPhase/3rdPartyResources.md)
* Exploration Phase : [Areas of Interest](docs/ExplorationPhase/AreasOfInterest.md)
* Exploration Phase : [Report](docs/ExplorationPhase/VulkanSceneGraphExplorationPhaseReport.md)
* PrototypePhase : [Workplan](docs/PrototypePhase/Workplan.md)
* PrototypePhase : [Report](docs/PrototypePhase/PrototypePhaseReport.md)

# VulkanSceneGraph library features

The [VulkanSceneGraph library](https://github.com/vsg-dev/VulkanSceneGraph/) provides the features that will be common to all applications - creating a viewer, windows, scene graph, reading/writing data, creating Vulkan objects and recording Vulkan commands, synchronizing with Vulkan processes and CPU threads, 3d vector maths and common utilities like computing bounds and intersection test and shader composition and cmpilation. The [vsg library headers](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg) are grouped in the following subdirectories:

* [app](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/app) - application level Vulkan classes
* [commands](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/commands) - scene graph nodes for Vulkan Commands
* [[core](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core) - base classes, smart pointer, data continers, allocators and visitor base classes
* [io](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io) - serialization and built-in reader/writers.
* [maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths) - GLSL style maths classes, similar to glm
* [vk](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/vk) - high level Vulkan integration such vkInstance/vkDevice etc.
* [nodes](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/) - scene graph nodes like groups, swtiches & transforms
* [platform](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/platform) - platform specific Windowing support
* [state](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/state) - scene graph objects for setting Vulkan state.
* [text](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/text) - text scene graph nodes
* [threading](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/threading) - threading classes and helper functions
* [ui](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/ui) - user interface classes such as mouse and keyboard events
* [utils](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/utils) - collection of utilities such intersections through to shader composition and compilation.
* [meshshaders](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/meshshaders) - Khronos Mesh Shader support
* [raytracing](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/raytracing) - Khronos Ray Tracing support

---

 Prev: [VulkanSceneGraphProject](VulkanSceneGraphProject.md)| Next: [BuildingVulkanSceneGraph](BuildingVulkanSceneGraph.md)
