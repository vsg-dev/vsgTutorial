---
layout: page
title: Performanmce Principles
permalink: /introduction/PerformancePrinciples
---

Efficiency of the design and implementation is critical to the projects success so took centre stage when evaluation different approaches to design and implementation, with the asperation of making each VulkanSceneGraph faetures 10 X faster than the equivilant feature in the OpenSceneGraph. Understanding what is happening in hardware to the data and how it is processed in each stage of the application is crucial to achieving this goal.

CPU bottlenecks with scene graph application predominantly occur during traversals of the scene graph, this is due to:
* scene graphs can contain 10's or 100's of thousands of objects and use many GBs of memory spread across nodes, textures and geometry data
* traversing large scene graph pushes the limits of memory bandwidth and CPU cache coherency, this was true in the 90's and is even more critical in 2020's
* CPU features like pre-fetch, branch prediction and instruction parallization are senstive to how data is arranged and how control flows.

Different CPUs have different strengths and weakness, some cope well with diffuse memory access and large numbers of branches, others struggle with challenging code and data. Taking care of how data is stored and how it is processed to avoid stressing the CPU and memory architechture can substantially improve CPU utilization and throughout. A series of design decisions were made for the VulkanSceneGraph to help make this happen:

* From the vsg::Object base class through to scene graphs nodes are kept as small as possible. Data members like names, description, masks and callbacks are avoided in most commonly used classes.
* A flexible meta data scheme is provided by a vsg::Axulixary classs that can be used on all objects when required, but in most cases will simply be the overhead of a null pointer.  This allows developers the flexibility to add names, descriptions etc when needed, without all objects paying the memory penalty.
* Scene graph callbacks are eliminated, with easy subclassing from scene graph nodes making this possible. Not having scene graph callbacks on nodes avoids the need to hold pointers to them and to check those pointers to see if custom behaivor is required.
* Scene graph node masks only exist on spefic node types where they are most useful, again this reduces memory footprint of nodes and avoids conditional statements.
* Dedicated nodes for scene graph culling like view frustum and LOD culling rather than having this functionality on all nodes avoids the need for a bounding volume data member on oall scene graph nodes, and avoids the need for checking if a cull test is required and any branching based on a cull test.
* Block memory allocator, vsg::Allocator, groups objects of similar type together into pre allocated blocks in memory. Nodes are packed togher, geometry and texture data are packed together etc.

Together these design descisions ensure:

* minimal object size so more objects can fit in main memory and crucially the CPU caches - vsg::Node takes just 24 bytes vs osg::Node 208 bytes.
* objects that will be operated on togeher are stored in memory together to increase the probablility that cachlines will contain objects that will be next accessed.
* conditional statements are reserved to just the places where they are required, rather than every where just in case they might be needed, so there is less branching, and when is needed branch prediction has a better chance of following the corect path.

The end result is scene graph traversals are around 10 times faster than the equivalent in the OpenSceneGraph. These are just a tester of the many performance related descisions in the VulkanSeneGraph, as you work through the vsgTutorial you'll be introduced to more tips and tricks that have been used, and ones that you can use in your own application development as well.

## 3rd party dependencies have to justify their inclusion

The VulkanSceneGraph library uses Vulkan, C++17 and CMake as external dependencies. The Vulkan C headers are used rather then the Vulkan C++ header which is unncessary as the Vulkan scene graph provides it's own encapsulation of Vulkan objects in a way that is coherent with how they are used in the scene graph.

For runtime shader compilation support the [glslang](https://github.com/KhronosGroup/glslang) library, orginally an optionally external dependency, but since VulkanSceneGraph-1.0.3 is now built internally as a submodule, this is compiled in by default but can be toggled off by setting the CMake VSG_SUPPORTS_ShaderCompiler variable to 0 before building the source. Compiling glslang within the VulkanSceneGraph library resolved problems with inconsistent 3rd party packaging of glslang, so now users can have seamlessly experience across platforms.

During the initial development of VulkanSceneGraph various other 3rd party dependencies, like gm and glfw, were considered for features like maths and windowing, but in each of these cases it was decided to implement the required features within the project rather than add an external dependency.  The reasons for implementing the functionality within the project:

* Coherent class interfaces and naming
* Coherent memory management
* Provide classes focused just on the needs of the VulkanSceneGraph users
* Avoid the glue code required to bring different libraries to work well together
* Keep memory and CPU overhead to a minimum
* Keep dependencies to a minimum to avoid ***Dependency Hell***
* Keep licensing simple and permissive

An example how local implementations can achieve what we need with far less code can be seen looking the glm maths library. It's a header only library with over 63,000 lines of code.  The VulkanSceneGraph has all GLSL style vector, quaternion and matrix functionality it needs in less than 3,000 lines of code. The VulkanSceneGraph code base has 57,000 lines of code for it's headers and source, and it has a scene graph, Vulkan integration, cross plarform windowing, viewer classes, serialization support and much more.

---

 Prev: [Vulkan](Vulkan.md)| Next: [VulkanSceneGraph Ecosystem](VulkanSceneGraphEcosystem.md)
