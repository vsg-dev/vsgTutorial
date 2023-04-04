---
layout: page
title: Data Types
permalink: /foundations/DataTypes
---

The scene graph needs to manage data that is held on the CPU and to be able to map this data to memory GPU in a coherent way.  The types of data may a single value, 1D, 2D and 3D arrays, with a range types, and used for a wide range of tasks - repreenting vertices, normals, texture coords arrays through to 1D, 2D and 3D textures.

The [vsg::Data](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Data.h) base class provides a common interface for all the different types of data, then a series of template classes provide support for both built-in types and user defined types for singel value, 1D, 2D and 3D arrays:

* [vsg::Value](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Value.h) - single value
* [vsg::Array](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array.h) - 1D fixed sized array
* [vsg::Array2D](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array2D.h) - 2D fixed sized array
* [vsg::Array3D](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core/Array3D.h) - 3D fixed size array

## vsg::Data base class

## vsg::Value

## vsg::Array

## vsg::Array2D

## vsg::Array3D



Prev: Next: [Math Types](MathTypes.md)| Next: [Meta Data](MetaData.md)

