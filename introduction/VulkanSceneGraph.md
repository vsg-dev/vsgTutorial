---
layout: page
title: VulkanSceneGraph - Vulkan Made Easy
permalink: /introduction/VulkanSceneGraph
---

The VulkanSceneGraph is Scene Graph library written specific for Vulkan. Like Vulkan is the successor to OpenGL, one that has wholly different API and architecture but retains the fundamental goal of providing a low level, open, cross platform, hardware abstraction, the VulkanSceneGarph is successor of the OpenSceneGraph, it's also an entirely different API and architecture but retains the fundenmtal goal of providing an open, cross patform high performance API for application developers.

## Guiding Principles: Produtivity and Performance

Vulkan makes it possible to get the most performance out of modern hardware, but it low level nature makes it harder to learn and use than OpenGL, in order to make all that performance available to a wider development community it's essential that we make it easier to use. To serve as a constant reminder of the importance of achieving this, the ***Vulkan Made Easy*** tag line was adopted for the vsg-dev github account.

The underlying principles that guided the VulkanSceneGraph development are desire to enable application developers to be as ***Productive*** as possible while delivering the best ***Performance*** possible.  These two are often competing principles, to deliever both at the same time requires good engineering - one must continually strive to write better class interfaces and implemnentations, to seek out simple yet flexible and efficient solutions.

## Approach to Development

The VulkanSceneGraph is an open source project and license and practice:
* From day 1 all work has been published on github and available to all under the [MIT](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/LICENSE.md) license.
* Fully embrace the capabilities of C++ 17, modern CMAke and Github for building software, managing software and communicating.
* Take lessons from developing the OpenSceneGraph, elements that are strong are updated and brought into the new scene graph, while flaws are recognized and used as driver for finding better solutions.
* To bring in lessons from the wider C++ community the [C++CoreGuidlines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) are used to guide class design and implementation.
* Spiral Development Model:  
Work follows a cycle starting at the centre and the moving around and outward following a spiral. On the innermost cycles of the spiral work is relatively simple and exploritory, but builds basic elements that later work can build upon, or on the next cycle round the sprial be revisted and refactored and made more capable if the original implementation is found insufficient. Steadily understanding of the problem domain is built and the software incrementally is built out in features and robustness.
* Not formally an [Agile Software Development](https://en.wikipedia.org/wiki/Agile_software_development) project but draws upon manifesto:
    * **Individuals and interactions** over processes and tools
    * **Working software** over comprehensive documentation
    * **Customer collaboration** over contract negotiation
    * **Responding to change** over following a plan 
    
During the initial development phase the follow documents and reports were written which provide a insight into design and implementation decisions:

* Design : [Design Principles & Philosophy](docs/Design/DesignPrinciplesAndPhilosophy.md)
* Design : [High Level Design Decisions](docs/Design/HighLevelDesignDecisions.md)
* Exploration Phase : [3rd Party Resources](docs/ExplorationPhase/3rdPartyResources.md)
* Exploration Phase : [Areas of Interest](docs/ExplorationPhase/AreasOfInterest.md)
* Exploration Phase : [Report](docs/ExplorationPhase/VulkanSceneGraphExplorationPhaseReport.md)
* PrototypePhase : [Workplan](docs/PrototypePhase/Workplan.md)
* PrototypePhase : [Report](docs/PrototypePhase/PrototypePhaseReport.md)

## Collection of libraries rather a Monolythic SDK

One of the flaws with the OoenSceneGraph project is that while it started as small scene graph library is step by step encompassed a wide range of components and features that are bundled together. While the OpenSceneGraph stops short of providing all the functionality of Game Engine it is bloated for the needs of many application develolopers.  Early in the VulknaSceneGraph project the decision was to create a core general purpose scene graph library and a collection of libraries each focused on specific features that users can easily compile and use in their applications if they need them.

The [VulkanSceneGraph library](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg) provides the features that will be common to almost applications:

* core - base classes, smart pointer, data continers, visitors
* maths - GLSL style maths classes.
* vk - appliction level Vulkan classes
* Still being written....

 Prev: [Vulkan](Vulkan.md)| Next: [BuildingVulkanSceneGraph](BuildingVulkanSceneGraph.md)
