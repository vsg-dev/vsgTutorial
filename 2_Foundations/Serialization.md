---
layout: page
    title: Serializaton
permalink: /foundations/Serializaton
---

The VulkanSceneGraph provides extensible serailization support so that all scene graph objects can be read/written from files and streams. This can be used with the native .vsgb binary and .vsgt ascii formats formats as well work with users defined input/ouput through to reading data compiled directly into example as illustrated in use of the vsgXchange::cpp ReaderWriter illustrated in the previous section on vsgXchange.

## vsg::Object, vsg::Input and vsg::Output bas classes

The serializtion support is built upon vsg::Object base class that provides virtual read(Input&) and write(Output&) methods that users override to implement support for their own member variables, and the vsg::Input and vsg::Output classes that provide a standarizaed interface for reading and writing data.  The [vsg::Object](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Object.h#L88) methods are:

~~~ cpp
virtual void read(Input& input);
virtual void write(Output& output) const;
~~~

The [vsg::Input](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Input.h) base class methods are:

The [vsg::Output](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Output.h) base class methods mirror those in vsg::Input:

## Ascii and Binary support

Prev: [vsgXchange](vsgXchange.md) | Next : [File Systems](FileSystem.md)

