---
layout: page
title: Maths Types
permalink: /foundations/MathsTypes
---

The VulkanSceneGraph provides GLSL style vector, quaternion and matrix types which are used both to represent data that can be used to store data on the CPU and can be directly mapped to GPU memory for use by shaders, and provides range of standard vector math functions.  We'll discuss the math functions later in this chapter, this page will disucss the data types.

## Data types

All the math types can be found in the [include/vsg/maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/) directory. All the types are declared as template<> structs with definitions provided for the specific types supporting bool, 8, 16 and 32 bit int and unsigned ints, float and double versions of each type. All the maths types are simple structs, only containing the data fields required for the type and are not subclassed from vsg::Object like other scene graph objects as their focus in representing low level data and supporting maths operations. The available types are and the headers that define them are follow.

Vector and quaternion types:
* vsg::vec2 [include/vsg/maths/vec2.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec2.h)
* vsg::vec3 [include/vsg/maths/vec3.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec3.h)
* vsg::vec4 [include/vsg/maths/vec4.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec4.h)
* vsg::quat [include/vsg/maths/quat.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/quat.h)

Matrix types:
* vsg::mat3 [include/vsg/maths/mat3.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat3.h)
* vsg::mat4 [include/vsg/maths/mat4.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat4.h)

Bounding volume primitive types:
* vsg::sphere [include/vsg/maths/sphere.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/spahre.h)
* vsg::box [include/vsg/maths/sphere.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/box.h)

## Vector


## Quaternion


## Matrices


## Bounding Volumes


---

Prev: [Block memory management with vsg::Allocator](Allocator.md)| Next: [Visitors](Visitors.md)
