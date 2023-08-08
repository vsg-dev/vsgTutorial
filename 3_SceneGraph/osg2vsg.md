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
| [`osg::Object`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Object) | [`vsg::Object`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Object.h)  | |

## Data classes

| OSG | VSG | Notes |
| --- | --- | --- |
| | [`vsg::Data`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Data.h) | Base class with no OSG equivalent |
| [`osg::Image`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Image) | [`vsg::Value<T>`, `vsg::Array<T>`, `vsg::Array2D<>`, `vsg::Array3D<T>`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/)  |  |
| [`osg::Uniform`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Uniform) | `vsg::Value<T>`, `vsg::Array<T>`, `vsg::Array2D<>`, `vsg::Array3D<T>` |  |
| [`osg::Array<T>`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Array) | [`vsg::Array<T>`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Array.h) |  |
| [`osg::IndexArray<T>`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Array) | [`vsg::Array<T>`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Array.h) |  |

## Scene graph nodes

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::Node`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Node) | [`vsg::Node`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Node.h)  |  |
| [`osg::Group`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Group) | [`vsg::Group`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Group.h)  |  |
| [`osg::Switch`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Switch) | [`vsg::Switch`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Switch.h)  |  |
| [`osg::LOD`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/LOD) | [`vsg::LOD`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/LOD.h)  |  |
| [`osg::PagedLOD`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/PagedLOD) | [`vsg::PagedLOD`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/PagedLOD.h)  |  |
| [`osg::Transform`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Transform) | [`vsg::Transform`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Transform,h)  | Both base classes for providing model transforms |
| [`osg::MatrixTransform`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/MatrixTransform) | [`vsg::MatrixTransform`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/MatrixTransform,h)  |  |
| [`osg::MatrixTransform`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/MatrixTransform.) | [`vsg::AbsoluteTransform`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/AbsoluteTransform,h)  |  osg::MatrixTransform::setReferenceFrame(ABSOLUTE_RF) equivalent to vsg::AbsoluteTransform |
| [`osg::PositionAttitudeTransform`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/PositionAttitudeTransform) |  | No VSG equivalent |
| [`osg::AutoTransform`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/AutoTransform) |  | No VSG equivalent |
| [`osg::Billboard`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Billboard) |  | No VSG equivalent - use instanced geometry and vertex shader. |

## State

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/) | [`vsg::`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/)  |  |

## Geometry

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osg::Drawable`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Drawable.h) | [`vsg::Command`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Command.h)  |  |
| [`osg::Geometry`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Geometry.h) | [`vsg::Geometry`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Geometry.h)  |  |
| [`vsg::PrimitiveSet`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/PrimitiveSet.h) | [`vsg::Draw`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Draw.h) |  |
| [`vsg::PrimitiveSet`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/PrimitiveSet.h) | [`vsg::DrawIndex`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/DrawIndexed.h) |  |
| | [`vsg::Commands`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Commands.h) | No OSG equivalent. |
| | [`vsg::VertexDraw`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/)  |  No direct OSG equivalent, closest is osg::Geometry |
| | [`vsg::VertexIndexDraw`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/)  |  No OSG equivalent, closest is osg::Geometry. |
| | [`vsg::BindVerteBuffers`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BindVerteBuffers.h) | No OSG equivalent. |
| | [`vsg::BindIndexBuffers`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BindIndexBuffers.h) | No OSG equivalent. |

## IO

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osgDB::readObjectFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile#L232) | [`vsg::read(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h)  |  |
| [`osgDB::readNodeFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile#L308) | [`vsg::read_cast<vsg::Node>(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h)  |  |
| [`osgDB::readImageFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReadFile#L268) | [`vsg::read_cast<vsg::Data>(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/read.h)  |  |
| [`osgDB::writeObjectFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/WriteFile) | [`vsg::write(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h)  |  |
| [`osgDB::writeNodeFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/WriteFile) | [`vsg::write(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h)  |  |
| [`osgDB::writeImageFile(..)`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/WriteFile) | [`vsg::write(..)`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/write.h)  |  |
| [`osgDB::Options`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/Options) | [`vsg::Options`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/Options.h)  |  |
| [`osgDB::FileCache`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/FileCache) | [`vsg::Options::fileCache`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/Options.h#L75)  |  |
| [`osgDB::ObjectCache`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ObjectCache) | [`vsg::SharedObjects`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/utils/SharedObjects.h)  |  |
| [`osgDB::ReaderWriter`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ReaderWriter) | [`vsg::ReaderWriter`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/ReaderWriter.h)  |  |
| [`osgDB::Registry`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/Registry) | [`vsg::ObjectFactory`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/ObjectFactory.h)  |  |
| [`std::string & UTF8`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/ConvertUTF8) | [`vsg::Path`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/Path.h)  |  OSG must be compiled with OSG_USE_UTF8_FILENAME, vsg::Path works like std::filesystem::path |
| [`osgDB::DatabasePager`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgDB/DatabasePager) | [`vsg::DatabasePager`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/io/DatabasePager.h)  |  |

## Application

| OSG | VSG | Notes |
| --- | --- | --- |
| [`osgViewer::`](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osgViewer/) | [`vsg::`](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/app/)  |  |

Prev : [Ray Tracing](RayTracing.md) | Next : [Next Chapter : Application](../4_Application/index.md)

