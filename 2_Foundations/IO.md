---
layout: page
title: IO
permalink: /foundations/IO
---

## Reading & Writing

The VulkanSceneGraph library provides reading/writing support for scene graph and associated objects to the native .vsgt ascii and .vsgb binary file format, as well as support for reading/wrting .spv SPIR-V shader files, the family of GLSL ascii shader files (.vert, .frag etc.).

Read functions can be found in [include/vsg/io/read.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h) header, the mostly comminly used functions used will be read and read_cast<T>:

~~~ cpp
// read a file and on success return vsg::ref_ptr<vsg::Object> to the loaded object
auto object = vsg::read("object.vsgt");

// use read_cast<T> to cast to specific type and ref_ptr<T> pointer
auto data = vsg::read_cast<vsg::Data>("image.vsgt");
~~~

Write function are found in [include/vsg/io/write.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h), usage is in form:

~~~ cpp
auto value = vsg::stringValue("mystring");
vsg::write(value, "value.vsgt");
~~~

## Options & vsgXchange

## ReaderWriter

## Serializaton


Prev: [Visitors](Visitors.md) | Next : [Block memory management with vsg::Allocator](../2_Foundations/Allocator.md)

