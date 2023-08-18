---
layout: page
title: Development Principles
permalink: /SettingTheScene/DevelopmentPrinciples
---

The VulkanSceneGraph Project goal is to make the development of high-performance graphics and compute applications quick and easy. Vulkan provides an excellent base for achieving high performance but is low-level and complicated to use. Simply wrapping a C API in C++ is not sufficient for application developers' needs, a collection of high-level features that make development easy is what is required. The ***Vulkan Made Easy*** tag line was adopted for the vsg-dev GitHub account as a daily reminder of our project's fundamental goal.

The VulkanSceneGraph library is built upon the Scene Graph concept and is written specifically for Vulkan. Just as Vulkan is the successor to OpenGL, one that has wholly different API and architecture but retains the fundamental goal of providing a low-level, open, cross platform hardware abstraction, the VulkanSceneGraph is successor to the OpenSceneGraph, it also has an entirely different API and architecture but retains the fundamental goal of providing an open, cross platform high-performance API for application developers.

## Productivity and Performance

The underlying principles that guided the VulkanSceneGraph development are the desire to enable application developers to be as ***Productive*** as possible while delivering the best ***Performance*** possible. These two are often competing principles, to deliver both at the same time requires good engineering - one must continually strive to write better class interfaces and implementations, to seek out simple yet flexible and efficient solutions.

The process of refining the software to better meet the needs of application developers won't stop with the VulkanSceneGraph-1.0 release, as the software develops these guiding principles will remain and we'll keep striving to deliver on the mantra Vulkan Made Easy.

As open-source middleware used by developers we aspire for the software to be not just useful for the functionality it provides, but also as an example of good software, illustrating how to write modern C++ software and avoid the many pitfalls of writing advanced software.

## Approach to Development

The VulkanSceneGraph is an open-source project in license and practice:
* From day 1 all work has been published on github and made available to all under the [MIT](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/LICENSE.md) license.
* Fully embrace the capabilities of C++ 17, modern CMake and GitHub for building software, managing software and communicating.
* Take lessons from developing the OpenSceneGraph, elements that are strong are updated and brought into the new scene graph, while flaws are recognized and used as a driver for finding better solutions.
* To bring in lessons from the wider C++ community the [C++CoreGuidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) are used to guide class design and implementation.
* Spiral Development Model:

Work follows a cycle starting at the centre and then moving around and outward following a spiral. On the innermost cycles of the spiral, work is relatively simple and exploratory but builds basic elements that later work can build upon, or on the next cycle round the spiral can be revisited, refactored and made more capable if the original implementation is found insufficient. Steadily, understanding of the problem domain is built and the software is incrementally built out in features and robustness.

* While not formally an [Agile Software Development](https://en.wikipedia.org/wiki/Agile_software_development) project we draw upon its manifesto:
    * **Individuals and interactions** over processes and tools
    * **Working software** over comprehensive documentation
    * **Customer collaboration** over contract negotiation
    * **Responding to change** over following a plan

## Only high value dependencies

The VulkanSceneGraph library only has C++17, CMake and Vulkan as external dependencies. The Vulkan C headers are used rather than the Vulkan C++ header which is unnecessary as the VulkanSceneGraph provides its own encapsulation of Vulkan objects in a way that is coherent with how they are used in the scene graph.

For runtime shader compilation support the VulkanSceneGraph library uses the [glslang](https://github.com/KhronosGroup/glslang) library. Originally integrated as an optional external dependency, it is now built internally as a submodule. While glslang support is compiled in by default it can be toggled off by setting the CMake VSG_SUPPORTS_ShaderCompiler variable to 0 before building the source. Compiling glslang within the VulkanSceneGraph library resolved problems with inconsistent 3rd party packaging of glslang, so now users can have a seamless experience across platforms.

During the initial development of VulkanSceneGraph various other 3rd party dependencies, like glm and glfw, were considered for features like maths and windowing, but in each of these cases it was decided to implement the required features within the project rather than add an external dependency. The reasons for implementing the functionality within the project were:

* Coherent class interfaces and naming
* Coherent memory management
* Provide classes focused just on the needs of the VulkanSceneGraph users
* Avoid the glue code required to make different libraries work well together
* Keep memory and CPU overhead to a minimum
* Keep dependencies to a minimum to avoid ***Dependency Hell***
* Keep licensing simple and permissive

An example of how local implementations can achieve what we need with far less code can be seen looking at the glm library. It's a header only library with over 63,000 lines of code. The VulkanSceneGraph has all GLSL style vector, quaternion, and matrix functionality it needs in less than 3,000 lines of code. The VulkanSceneGraph code base has 57,000 lines of code for its headers and source, and it has a scene graph, Vulkan integration, cross platform windowing, viewer classes, serialization support and much more.

---

Prev: [High-level APIs](HighLevelAPIs.md)| Next: [Performance Principles](PerformancePrinciples.md)
