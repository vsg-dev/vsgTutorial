---
layout: page
title: Performance Principles
permalink: /SettingTheScene/PerformancePrinciples
---

Efficiency of the design and implementation is critical to the project's success so took centre stage when evaluating different approaches to design and implementation, with the aspiration of making each VulkanSceneGraph feature 10 X faster than the equivalent feature in the OpenSceneGraph.  Understanding what is happening in hardware to the data and how it is processed in each stage of the application is crucial to achieving this goal.

CPU bottlenecks with scene graph application predominantly occur during traversals of the scene graph, this is due to:
* Scene Graphs can contain tens or hundreds of thousands of objects and use many GBs of memory spread across nodes, textures and geometry data
* Traversing large scene graphs pushes the limits of memory bandwidth and CPU cache coherency, this was true in the 90's and is even more critical in 2020's
* CPU features like pre-fetch, branch prediction and instruction parallelization are sensitive to how data is arranged and how control flows are structured

Different CPUs have different strengths and weaknesses, some cope well with diffuse memory access and large numbers of branches, others struggle with such challenging code and data.  Taking care of how data is stored and processed to avoid stressing the CPU and memory architecture can substantially improve CPU utilization and throughput.  A series of design decisions were made for the VulkanSceneGraph to help make this happen:

* From the [vsg::Object](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Object.h) base class through to scene graph nodes, classes are kept as small as possible.  Data members like names, descriptions, masks and callbacks are avoided in the most commonly used classes.
* A flexible meta data scheme is provided by a [vsg::Auxiliary](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Auxiliary.h) class that can be used on all objects when required, but in most cases will simply be the overhead of a null pointer.  This allows developers the flexibility to add names, descriptions etc when needed, without all objects paying the memory penalty.
* Scene graph callbacks are eliminated, with easy subclassing from scene graph nodes making this possible.  Not having scene graph callbacks on nodes avoids the need to hold pointers to them and to check those pointers to see if custom behaviour is required.
* Scene graph node masks only exist on specific node types where they are most useful, again reducing memory footprint of nodes and avoiding conditional statements.
* Dedicated nodes for scene graph culling like view frustum and LOD culling rather than having this functionality on all nodes avoids the need for a bounding volume data member on all scene graph nodes, and avoids the need for checking if a cull test is required and any branching based on a cull test.
* A block memory allocator, the [https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Allocator.h](vsg::Allocator), groups objects of similar type together into pre allocated blocks in memory.  Nodes are packed together, geometry and texture data are packed together etc.

Together these design decisions ensure:

* minimal object size so more objects can fit in main memory and crucially the CPU caches - vsg::Node takes just 24 bytes vs osg::Node 208 bytes.
* objects that will be operated on together are stored in memory together to increase the probability that cache lines will contain objects that will be next accessed.
* conditional statements are reserved to just the places where they are required, rather than everywhere just in case they might be needed, so there is less branching, and branch prediction has a better chance of following the correct path.

The end result is scene graph traversals that are around 10 times faster than the equivalent in the OpenSceneGraph.  These are just a taste of the many performance related decisions in the VulkanSceneGraph, as you work through the vsgTutorial you'll be introduced to more tips and tricks that have been used, and ones that you can use in your own application development as well.

---

Prev: [Development Principles](DevelopmentPrinciples.md) | Next: [Ecosystem](Ecosystem.md)
 
