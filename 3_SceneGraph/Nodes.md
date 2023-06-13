---
layout: page
title: Nodes
permalink: /scenegraph/Nodes
---

The class definitions for the Internal nodes of the scene graph can bound found the [VulkanSceneGraph/include/vsg/nodes](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/) directory.

| Class | Header | Functionality |
| vsg::Node | [Node.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Node.h) | Node base class |


| Group nodes | Header | Functionality |
| vsg::Group | [Group.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Group.h) | Group node |
| vsg::QuadGroup | [QuadGroup.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/QuadGroup.h) | Quadgroup is fixed sized group for building high performance quad trees |
| vsg::Switch | [Switch.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Switch.h) | Switch node provides support for switching between children |


| Culling nodes| Header | Functionality |
| vsg::CullGroup | [CullGroup.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/CullGroup.h) | Culling group that has culls a bounding sphere against view frustum |
| vsg::CullNode | [CullNode.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/CullNode.h) | Culling node that has culls a bounding sphere against view frustum |
| vsg::LOD | [LOD.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/LOD.h) | Level of Detail node that culls based on projected size of bounding sphere |
| vsg::PagedLOD | [PagedLOD.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/PagedLOD.h) | Level of Detall node that has a low res child and high res child with file reference  |
| vsg::TileDatabase | [TileDatabase.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/TileDatabase.h) | |


| Transformation nodes| Header | Functionality |
| vsg::Transform| [Transform.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Transform..h) | Transform base class node that provides a interface for definiting transforms of a subgraph  |
| vsg::MatrixTransform | [MatrixTransform.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/MatrixTransform.h) | Transform node that provides a 4x4 matrix to transform relative to parent coordinate frame |
| vsg::AbsoluteTransform | [AbsoluteTransform.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/AbsoluteTransform.h) | Transform node that provides a 4x4 matrix that ignores parent coordinate frame to provide an absolute frame of reference |

| Geometry nodes | Header | Functionality |
| vsg::Geometry | [Geometry.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Geometry.h) | |
| vsg::VertexDraw | [VertexDraw.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/VertexDraw.h) | |
| vsg::VertexIndexDraw | [VertexIndexDraw.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/VertexIndexDraw.h) | |

| State nodes | Header | Functionality |
| vsg::StateGroup | [StateGroup.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/StateGroup.h) | |
| vsg::Light | [Light.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Light.h) | |
| Draw order control | |
| vsg::Bin | [Bin.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Bin.h) | |
| vsg::DepthSorted | [DepthSorted.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/DepthSorted.h) | |
| | |
| vsg::Compileable | [Compilable.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Compilable.h) | |

Prev: [Scene Graph](index.md)| Next: [Commands](Commands.md)

