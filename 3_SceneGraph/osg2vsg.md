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

## State

| OSG | VSG | Notes |
| --- | --- | --- |

## Geometry

| OSG | VSG | Notes |
| --- | --- | --- |

## IO

| OSG | VSG | Notes |
| --- | --- | --- |

## Application

| OSG | VSG | Notes |
| --- | --- | --- |

Prev : [Ray Tracing](RayTracing.md) | Next : [Next Chapter : Application](../4_Application/index.md)

