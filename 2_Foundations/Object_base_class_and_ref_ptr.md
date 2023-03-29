---
layout: page
title: Base classes and smart pointers
permalink: /foundations/BaseClassesAndSmartPointers
---

To provide robust, thread-safe, high performance memory manangment the VulkanSceneGraph uses intrusive reference counting and block memory allocation. The three main classes that provide this functionality are vsg::Object base class, the vsg::ref_ptr<> smart pointer and vsg::Allocator singleton. The vsg::Auxilary class and vsg::observer_ptr<> smart pointer provide additional meta data and weak pointer functionality.  In this section we'll covert the vsg::Object base class and the vsg::ref_ptr<> smart pointer and cover the vsg::Auxiliary, observer_ptr<> and vsg::Allocator in the follow two sections.

## Intrusive vs non-instrusive reference counting

Reference counting is widely used in application to facilitate robust sharing of objects allocated on the heap.  The two main approaches used in C++ applications are itrusive and on intrusive reference counting, each have strengths and weaknesses.

Standard C++ provides the std::shared_ptr<> smart pointer that uses non-instrusive counting. The design requires the shared_ptr<> to hold two pointers, one to the object being managed and one to a shared refernce count. The advantage of non intrusive reference counting is that it can be used with all types, from bool to std::vector to user classes. The disadvantage of the shared_ptr<> is twice the size of a C pointer which has singinficant performance consequences which we'll discuss in detail below.

With intrusive reference counting the count is placed into the object, in the case of the VulkanSceneGraph is this is provided by the vsg::Object base classes atomic _referneceCount member variable which is accessed via the ref() and unref() methods that increament and decrement the count and when the count goes to zero the object is automatically deleted. To ensure that the ref() and unref() methods are called consistently the vsg::ref_ptr<> smart pointer is provided, similar in role to the std::shared_ptr<>, but has the advantage that it only requires a single C pointer so is the same size as a C pointer, and half the memory footprint of the std::shared_ptr<>.  The disadvantage with intrusive reference counting is that you can not use it directly with types like bool etc. 

For the case of a scene graph we have a data structure where the internal nodes of the graph are primarily pointers to data objecs or other nodes in the scene graph, if you double the size of the pointer you close to double the size of internal nodes in the graph.  Increasing the size of the nodes means you require more memory and crucially can fit less nodes into cache which means more cache misses and lower CPU utilization.  Benchmarking done comparing the traversal speeds of scene graph uses std::shared_ptr<> vs one with vsg::ref_ptr<> show that the intrusive reference counted scene graph is 15% faster.

## Using vsg::Object and ref_ptr<>




---

Prev: [Foundations](index.md)| Next: [Meta data, vsg::Auxiliary and vsg::observer_ptr<>](Auxiliary_and_observer_ptr.md)

