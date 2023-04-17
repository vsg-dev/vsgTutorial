---
layout: page
title: Input & Output
permalink: /foundations/IO
---

The VulkanSceneGraph provides extensiuble support for reading/writing scene graph and asscated objects. Extensibility can be found at the low level of serializaton support for individual objects and high level with ReaderWriters that support reading/writing of single or collections of objects to files/streams.   Cross platform file system functionality is also provided where C++17 support is lacking. An extensible vsg::Logger and i/ostrream support for native types rounds out functionality found in the [include/vsg/io](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io) directory.

## Reading & Writing

The VulkanSceneGraph library provides extensible reading/writing support for scene graph and associated objects via the vsg::ReaderWriter class.  Subclasses of RenaderWriter provided by the VulkanSceneGraph library itself are:

* [vsg::VSG](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/vsg.h) - reading/writing native .vsgt ascci & .vsgb binary file format
* [vsg::spirv](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/spv.h) - reading/wiring .spv SPIRV shader files
* [vsg::glsl](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/glsl.h) - reading GLSL shader files.
* [vsg::txt](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/txt.h) - reading text files as vsg::stringValue for later parsing by users
* [vsg::tile](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/tile.h) - native tile based database paging

Developers may call ReaderWriter directly, but for must usage cases they will use the vsg::read() and read_cast<T>() functions that are found in [include/vsg/io/read.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h) header. The vsg::read*() functions will invoke the appropriate ReaderWriter based on the file extension, usage:

~~~ cpp
// read a file and on success return vsg::ref_ptr<vsg::Object> to the loaded object
auto object = vsg::read("object.vsgt");

// use read_cast<T> to cast to specific type and ref_ptr<T> pointer
auto data = vsg::read_cast<vsg::Data>("image.vsgt");

// use read_cast<T> to cast to specific type and ref_ptr<T> pointer
auto vertexShader = vsg::read_cast<vsg::ShaderStage>("shader.vert");
~~~

Write function are found in [include/vsg/io/write.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h), usage is in form:

~~~ cpp
// create an object
auto value = vsg::stringValue("mystring");

// write to native ascii file format
vsg::write(value, "value.vsgt");
~~~

## Options & vsgXchange

Customization and extension of reading and writing is provided by the vsg::Options object that can be passed to the vsg;:read(..) and vsg::write(..) methods. You can pass in the ReaderWriters

## ReaderWriter

## Serializaton

## vsg::Path and file system functions

## i/ostream support for native types

## Logger

Prev: [Visitors](Visitors.md) | Next : [Block memory management with vsg::Allocator](../2_Foundations/Allocator.md)

