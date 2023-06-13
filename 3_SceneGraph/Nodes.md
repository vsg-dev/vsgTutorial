---
layout: page
title: Nodes
permalink: /scenegraph/Nodes
---

The class definitions for the Internal nodes of the scene graph can bound found the [VulkanSceneGraph/include/vsg/nodes](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/) directory.

## Node Base class

| Class | Header | Functionality |
| vsg::Node | [Node.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Node.h) | Node base class |

## Group nodes

| Group nodes | Header | Functionality |
| vsg::Group | [Group.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Group.h) | Group node |
| vsg::QuadGroup | [QuadGroup.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/QuadGroup.h) | Quadgroup is fixed sized group for building high performance quad trees |
| vsg::Switch | [Switch.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Switch.h) | Switch node provides support for switching between children |

## Culling nodes

| Culling nodes| Header | Functionality |
| vsg::CullGroup | [CullGroup.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/CullGroup.h) | Culling group that has culls a bounding sphere against view frustum |
| vsg::CullNode | [CullNode.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/CullNode.h) | Culling node that has culls a bounding sphere against view frustum |
| vsg::LOD | [LOD.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/LOD.h) | Level of Detail node that culls based on projected size of bounding sphere |
| vsg::PagedLOD | [PagedLOD.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/PagedLOD.h) | Level of Detall node that has a low res child and high res child with file reference  |
| vsg::TileDatabase | [TileDatabase.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/TileDatabase.h) | |

## Transformation nodes

| Transformation nodes| Header | Functionality |
| vsg::Transform| [Transform.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Transform..h) | Transform base class node that provides a interface for definiting transforms of a subgraph  |
| vsg::MatrixTransform | [MatrixTransform.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/MatrixTransform.h) | Transform node that provides a 4x4 matrix to transform relative to parent coordinate frame |
| vsg::AbsoluteTransform | [AbsoluteTransform.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/AbsoluteTransform.h) | Transform node that provides a 4x4 matrix that ignores parent coordinate frame to provide an absolute frame of reference |

## Geometry nodes

| Geometry nodes | Header | Functionality |
| vsg::Geometry | [Geometry.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Geometry.h) | General purpose geometry node provides a list of arrays and list of draw commands |
| vsg::VertexDraw | [VertexDraw.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/VertexDraw.h) | High performance geometry node provides a list of arrays and a single draw command |
| vsg::VertexIndexDraw | [VertexIndexDraw.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/VertexIndexDraw.h) | High performance geometry node provides a list of arrays, an index array and a single indexed draw command |

## State nodes

| State nodes | Header | Functionality |
| vsg::StateGroup | [StateGroup.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/StateGroup.h) | State group node that provides a list of StateCommands to decorate a subgraph |
| vsg::Light | [Light.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Light.h) | Light node provides all the settings for positing and controlling the type, color of a light source |

## Draw order control

| Draw order control | Header | Functionality |
| vsg::Bin | [Bin.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Bin.h) | Bin node provides a way of controlling the record order of its children |
| vsg::DepthSorted | [DepthSorted.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/DepthSorted.h) | Depth sorted node provides controls for depth sorting of it's subgraph |


Prev: [Scene Graph](index.md)| Next: [Commands](Commands.md)

