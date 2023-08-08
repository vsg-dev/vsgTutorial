---
layout: page
title: OpenSceneGraph to VulkanSceneGraph
permalink: /scenegraph/osg2vsg
---

## Smart pointers

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::ref_ptr<T>`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/ref_ptr) | [`vsg::ref_ptr<T>`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/ref_ptr.h) |  |
| [`osg::observer_ptr<T>`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/observer_ptr) | [`vsg::observer_ptr<T>`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/observer_ptr.h)  |


## Base classes

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::Referenced`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Referenced) | [`vsg::Object`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Object.h) |  |
| [`osg::Object`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Object) | [`vsg::Object`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Object.h)  |

## Data classes

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::Image`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Image) | [`vsg::Value<T>`, `vsg::Array<T>`, `vsg::Array2D<>`, `vsg::Array3D<T>`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/)  |  |
| [`osg::Uniform`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Uniform) | `vsg::Value<T>`, `vsg::Array<T>`, `vsg::Array2D<>`, `vsg::Array3D<T>` |  |
| [`osg::Array<T>`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Array) | [`vsg::Array<T>`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Array.h) |  |
| [`osg::IndexArray<T>`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Array) | [`vsg::Array<T>`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Array.h) |  |

## Scene graph nodes

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/) | [`vsg::`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/)  |  |

## State

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/) | [`vsg::`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/)  |  |

## Geometry

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::Drawable`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Drawable.h) | [`vsg::Command`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Command.h)  |  |
| [`osg::Geometry`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/) | [`vsg::Geometry`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/)  |  |

## IO

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osgDB::readObjectFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile) | [`vsg::read(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h)  |  |
| [`osgDB::readNodeFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile) | [`vsg::read_cast<vsg::Node>(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h)  |  |
| [`osgDB::readImageFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile) | [`vsg::read_cast<vsg::Data>(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h)  |  |
| [`osgDB::writeObjectFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile) | [`vsg::write(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h)  |  |
| [`osgDB::writeNodeFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile) | [`vsg::write(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h)  |  |
| [`osgDB::writeImageFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile) | [`vsg::write(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h)  |  |
| [`osgDB::Options`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/Options) | [`vsg::Options`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/Options.h)  |  |
| [`osgDB::FileCache`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/FileCache) | [`vsg::Options::fileCache`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/Options.h#L75)  |  |
| [`osgDB::ObjectCache`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/Options) | [`vsg::SharedObjects`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/utils/SharedObjects.h)  |  |
| [`osgDB::ReaderWriter`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/) | [`vsg::ReaderWriter`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/)  |  |
| [`osgDB::Registry`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/Registry.h) | [`vsg::ObjectFactory`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/ObjectFactory.h)  |  |

## Application

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osgViewer::`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgViewer/) | [`vsg::`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/app/)  |  |

Prev : [Ray Tracing](RayTracing.md) | Next : [Next Chapter : Application](../4_Application/index.md)

