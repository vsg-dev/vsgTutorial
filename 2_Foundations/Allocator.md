---
layout: page
title: Block allocation with vsg::Allocator
permalink: /foundations/Allocator
---

Memory bandwidth is fundemental bottleneck for graphics applications, both on the CPU in main memory and on the GPU. On the CPU side the scene graph traversal stresses the CPU cache and memory bandwidth, over the decades CPUs have got faster at a quicker rate than memory bandidth so the issue of CPUs stalled waiting for instructions and data to be pulled from main memory has become an even more critical bottleneck. The VulkanSceneGraph minimizes cache misses and bandwidth load in two main ways:

1. Minmizing scene graph object size
2. Block allocation of similar object types within the same memory blocks

In the earlier sections of this chapter we discussed how scene graph object size is kept to a minimum, in this section we'll discuss how the [vsg::Allocator](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Allocator.h) provides block allocation and binning similar object types within the same blocks.

## Allocator example

The [vsgallocator](https://github.com/vsg-dev/vsgExamples/tree/master/examples/core/vsgallocator.cpp) example illustrates how to write a custom vsg::Allocator class, how to report memory usage from the vsg::Allocator and control the block sizes and performance reporting.

---

Prev: [Streams & Logger](StreamsAndLogger.md)| Next: [Maths Functions](MathFunctions.md)

