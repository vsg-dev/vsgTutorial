---
layout: page
title: Streams & Logger
permalink: /foundations/StreamsAndLogger
---

A significant part of developing software is the process of reporting and logging results for the purpose of QA and debugging. C++ provides the std::ostream/std::istream operators for convinient textural formatting output and inputing of standard types, and the VulkanSceneGraph extends this to include native types.  The library then adds additional support for recording textural with an extensible thread safe logger class.

## iostream & iostream operators

The [include/vsg/io/streams.h header](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/streams.h#L37) provides a collection of << and >> operators for a range of types making it convinient to report values to console or to streams:

~~~ cpp
vsg::vec3 position = {1.0, 2.0, 3.0};

vsg::vec4 rotation = {1.0, 2.0, 3.0, 0.0};

vsg@:mat4 matrix = { 2.0, 0.0, 0.0, 0.0,
                     0.0, 2.0, 0.0, 0.0,
                     0.0, 0.0, 2.0, 0.0,
                     0.0, 0.0, 0.0, 1.0};

auto place = vsg::stringValue("Paris");

std::cout<<"position = "<<position<<std::endl;
std::cout<<"rotation = "<<rotation<<std::endl;
std::cout<<"matrix = "<<matrix<<std::endl;
std::cout<<"place = "<<place<<std::endl;
~~~

## vsg::Logger



Prev: [File System](FileSystem.md) | Next : [Block memory management with vsg::Allocator](Allocator.md)

