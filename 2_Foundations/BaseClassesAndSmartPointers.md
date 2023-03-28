---
layout: page
title: Foundations
permalink: /foundations/BaseCalssesAndSmartPointers
---

Topics to cover:

1. non intrusive vs intrusive reference counting
1. vsg::Object class and vsg::ref_ptr<>
1. Meta data, vsg::Auxiliary and vsg::observer_ptr<>
1. vsg::Allocator

--- 

To provide robust and high performance memory manangment the VulkanSceneGraph uses intrusive reference counting and block memory allocation. While these features are built using C++17 features they differ from the C++ built-in std::shared_ptr<> and new/delete, the motivation for providing local implementation of these features is purely for scalability and performance by reducing memory overhead and improving cache coherency.

---

Prev: [Foundations](index.md)| Next: [Maths](Maths.md)

