---
layout: page
title: Block allocation with vsg::Allocator
permalink: /foundations/Allocator
---

Memory bandwidth is a fundamental bottleneck for graphics applications, both on the CPU in main memory and on the GPU. On the CPU side the scene graph traversal stresses the CPU cache and memory bandwidth, over the decades CPUs have become faster at a quicker rate than memory bandwidth so the issue of CPUs stalled waiting for instructions and data to be pulled from main memory has become an even more critical bottleneck. The VulkanSceneGraph minimizes cache misses and bandwidth load in two main ways:

1. Minimizing scene graph object size
2. Block allocation of similar object types within the same memory blocks

In the earlier sections of this chapter we discussed how scene graph object size is kept to a minimum, in this section we'll discuss how the [vsg::Allocator](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Allocator.h) provides block allocation and binning similar object types within the same blocks.

## How vsg::Allocator works

The vsg::Allocator is a singleton that is invoked by vsg::allocate(..) and vsg::deallocate(..) function calls, which users can use like malloc(..)/free(..), but in normal usage will be called for you by custom new/delete implementations for vsg::Node, vsg::Data and vsg::Object respectively.  The custom new/delete implementations will be invoked automatically when you call **new vsg::Group** as well as the standard usage of **vsg::Group::create()**. This integration means that VukanSceneGraph users need not do anything to enable use of the vsg::Allocator - it all works out of the box.

The custom new/delete implementations call vsg::allocate() with the type of object so that the vsg::Allocator can allocate the memory from preallocated blocks associated with the object type, this ensures that all vsg::Node subclasses get allocated within memory blocks alongside other nodes, all vsg::Data get allocated in data blocks and all other vsg::Object subclasses get allocated together.

The default block size is 16Mb, users can override this by calling [vsg::Allocator::setBlockSize(AllocatorAffinity, size_t)](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Allocator.h#L115) i.e.

~~~ cpp
    vsg::Allocator::instance()->setBlockSize(vsg::ALLOCATOR_AFFINITY_OBJECTS, objectsBlockSize);
    vsg::Allocator::instance()->setBlockSize(vsg::ALLOCATOR_AFFINITY_NODES, nodesBlockSize);
    vsg::Allocator::instance()->setBlockSize(vsg::ALLOCATOR_AFFINITY_DATA, dataBlockSize);
~~~

## vsg::Allocator example

The [vsgallocator](https://github.com/vsg-dev/vsgExamples/tree/master/examples/core/vsgallocator/vsgallocator.cpp) example illustrates how to write a custom vsg::Allocator class, how to report memory usage from the vsg::Allocator and control the block sizes and performance reporting.

One of the roles of vsgallocator has been to test the performance impact of the different allocators, the following are tests of loading a big city model then running 10,000 traversals through the whole scene graph to collect node and state stats, the first run below is the default allocator that the VulkanSceneGraph provides, the second is using standard C++ new/delete - the vsg::Allocator provides a 90% speed up of traversals just from allocating nodes, objects and data in their own blocks respectively.

~~~ sh
# default block allocator
$ vsgallocator --num-stats 10000 bigcity.vsgb --no-viewer
Stats collection took 1628.76ms for 10000 traversals.

# use new/delete instead of block allocator
$ vsgallocator --num-stats 10000 bigcity.vsgb --no-viewer --allocator 1
Stats collection took 3087.37ms for 10000 traversals.
~~~

Rendering performance test, here we see overall framerate improves by 42% when using the default block allocator rather than the standard C++ new/delete:

~~~ sh
$ vsgallocator bigcity.vsgb -f 10000 --st -p path1.path
load duration = 92.0588ms
release duration  = 89.3268ms
delete duration  = 5.52642ms
Average frame rate = 1618.85fps

# use new/delete instead of block allocator
$ vsgallocator bigcity.vsgb  --allocator 1 -f 10000 --st -p path1.path
load duration = 71.1517ms
release duration  = 37.7424ms
delete duration  = 0.00416ms
Average frame rate = 1143.24fps
~~~

While we see significant improvements in performance for scene graph traversals and rendering performance the vsg::Allocator does presently add an overhead when allocating and deleting objects as seen by the slightly longer load, release and delete times shown above. The initial focus in development of the vsg::Allocator has been improving performance of traversals and rendering of the scene graph rather than lowering start up/shutdown speed, longer term it is planned to optimize the allocation and deallocation algorithm to lower this overhead.

---

Prev: [Streams & Logger](StreamsAndLogger.md)| Next: [Maths Functions](MathFunctions.md)
