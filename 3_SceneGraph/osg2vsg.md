---
layout: page
title: OpenSceneGraph to VulkanSceneGraph
permalink: /scenegraph/osg2vsg
---


## Base classes

| OSG | VSG | Notes |
| --- | --- | --- |
| osg::Referenced | vsg::Object |  |
| osg::Object | vsg::Object |  |

## Data classes

| OSG | VSG | Notes |
| --- | --- | --- |
| osg::Image | vsg::Value<T>, vsg::Array<T>, vsg::Array2D<>, vsg::Array<3D>  |  |
| osg::Uniform | vsg::Value<T>, vsg::Array<T>, vsg::Array2D<>, vsg::Array<3D> |  |
| [osg::Array<T>](https://github.com/openscenegraph/OpenSceneGraph/blob/master/include/osg/Array) | [vsg::Array<T>](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/core/Array.h) |  |
| osg::IndexArray<T> | vsg::Array<T> |  |

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

