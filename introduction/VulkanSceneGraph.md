---
layout: page
title: VulkanSceneGraph - Vulkan Made Easy
permalink: /introduction/VulkanSceneGraph
---

The VulkanSceneGraph is Scene Graph library written specific for Vulkan. Like Vulkan is the successor to OpenGL, one that has wholly different API and architecture but retains the fundamental goal of providing a low level, open, cross platform, hardware abstraction, the VulkanSceneGarph is successor of the OpenSceneGraph, it's also an entirely different API and architecture but retains the fundenmtal goal of providing an open, cross patform high performance API for application developers.

## Guiding Principles: Productivity and Performance

Vulkan makes it possible to get the most performance out of modern hardware, but it low level nature makes it harder to learn and use than OpenGL, in order to make all that performance available to a wider development community it's essential that we make it easier to use. To serve as a constant reminder of the importance of achieving this, the ***Vulkan Made Easy*** tag line was adopted for the vsg-dev github account.

The underlying principles that guided the VulkanSceneGraph development are desire to enable application developers to be as ***Productive*** as possible while delivering the best ***Performance*** possible.  These two are often competing principles, to deliever both at the same time requires good engineering - one must continually strive to write better class interfaces and implemnentations, to seek out simple yet flexible and efficient solutions.

The process of refining the software to better meet the needs of application developers won't stop with the VulkanSceneGraph-1.0 release, as the software develops these guiding principles will remain and we'll keep striving to deliver on the matra Vulkan Made Easy.

## Approach to Development

The VulkanSceneGraph is an open source project and license and practice:
* From day 1 all work has been published on github and available to all under the [MIT](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/LICENSE.md) license.
* Fully embrace the capabilities of C++ 17, modern CMAke and Github for building software, managing software and communicating.
* Take lessons from developing the OpenSceneGraph, elements that are strong are updated and brought into the new scene graph, while flaws are recognized and used as driver for finding better solutions.
* To bring in lessons from the wider C++ community the [C++CoreGuidlines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) are used to guide class design and implementation.
* Spiral Development Model:
Work follows a cycle starting at the centre and the moving around and outward following a spiral. On the innermost cycles of the spiral work is relatively simple and exploritory, but builds basic elements that later work can build upon, or on the next cycle round the sprial be revisted and refactored and made more capable if the original implementation is found insufficient. Steadily understanding of the problem domain is built and the software incrementally is built out in features and robustness.
* Not formally an [Agile Software Development](https://en.wikipedia.org/wiki/Agile_software_development) project but draws upon it's manifesto:
    * **Individuals and interactions** over processes and tools
    * **Working software** over comprehensive documentation
    * **Customer collaboration** over contract negotiation
    * **Responding to change** over following a plan

## Design and Development Reports

During the initial development phase the follow documents and reports were written which provide a insight into design and implementation decisions:

* Design : [Design Principles & Philosophy](docs/Design/DesignPrinciplesAndPhilosophy.md)
* Design : [High Level Design Decisions](docs/Design/HighLevelDesignDecisions.md)
* Exploration Phase : [3rd Party Resources](docs/ExplorationPhase/3rdPartyResources.md)
* Exploration Phase : [Areas of Interest](docs/ExplorationPhase/AreasOfInterest.md)
* Exploration Phase : [Report](docs/ExplorationPhase/VulkanSceneGraphExplorationPhaseReport.md)
* PrototypePhase : [Workplan](docs/PrototypePhase/Workplan.md)
* PrototypePhase : [Report](docs/PrototypePhase/PrototypePhaseReport.md)

## Collection of libraries rather than a Monolythic SDK

One of the flaws with the OoenSceneGraph project is that while it started as small scene graph library step by step encompassed a wider range of components and features that are bundled together. While the OpenSceneGraph stops short of providing all the functionality of Game Engine it is bloated for the needs of many application develolopers.  Early in the VulkanSceneGraph project the decision was made to create a core general purpose scene graph library and a collection of libraries each focused on specific features that users can easily compile and use in their applications if they need them.

While the VulkanSceneGraph is focused on the core features used by all graphics application developers, it should make a excellent base coompopnent for higher level Image Generation (IG) SDK or Game Engine SDKs.

The [vsg-dev](https://github.com/vsg-dev) github account hosts the following projects which are officially supported as part the VulkanSceneGraph project, the three main projects that majority of developers will need to use are:
* [VulkanSceneGraph](https://github.com/vsg-dev/VulkanSceneGraph)  
The VulkanSceneGraph library itself is capable of used on it's own for stand alone graphics applications, and for embedded platforms this may be the desired approach as it will minimize the code base that needs to be QA'd for sercurity and robustness, and minimzes the final exectuble size.
* [vsgXchange](https://github.com/vsg-dev/vsgXchange)  
It is expected for most desktop applications users will also want to load a range of 3rd iamge and 3d model data, to support this usage case the  library adds support for a wide range of image and 3d model formats, using assimp, as well as support for reading data from http/https using libcurl, and reading/writing/processing of GIS imagery and DEMS through the optional GDAL integration.
* [vsgExamples](https://github.com/vsg-dev/vsgExamples)  
A collection of 59 examples (as of 20th March 2023) that have written to help test VulkanSceneGraph features as they are developed and as an educational tool for new users.

Also hosted on vsg-dev are more specialist projects:

* [osg2vsg](https://github.com/vsg-dev/osg2vsg) - osg2vsg library for converting data and integrating OpenGL/OSG and Vulkan/VSG applications.
* [vsgImGui](https://github.com/vsg-dev/vsgImGui) - ImGui and ImPlot integration with the VulkanSceneGraph
* [vsgQt](https://github.com/vsg-dev/vsgQt) - Qt5/Qt6 integrtation with the VulkanSceneGraph
* [vsgUnity](https://github.com/vsg-dev/vsgUnity) - plugin for the Unity Editor for expoting VulkanSceneGraph models
* [MyFirstVsgApplication](https://github.com/vsg-dev/MyFirstVsgApplication) - simple stanndalone example illustrating the CMake and C++ required.


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

 Prev: [Vulkan](Vulkan.md)| Next: [BuildingVulkanSceneGraph](BuildingVulkanSceneGraph.md)
