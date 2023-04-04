---
layout: page
title: Maths Types
permalink: /foundations/MathsTypes
---

The VulkanSceneGraph provides GLSL style vector, quaternion and matrix types which are used both to represent data that can be used to store data on the CPU and can be directly mapped to GPU memory for use by shaders, and provides range of standard vector math functions.  We'll discuss the math functions later in this chapter, this page will disucss the data types.

## Data types

All the math types can be found in the [include/vsg/maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/) directory. All the types are declared as template<> structs with definitions provided for the specific types supporting bool, 8, 16 and 32 bit int and unsigned ints, float and double versions of each type. The prefix of the type describes the type, the prefix to type mapping are:

| Prefix | Description | Type | Example |
| no prefix | 32 bit floating point | float | vsg::vec3 |
| d | 64 bit floating point | double | vsg::dmat4 |
| b | signed byte | std::int8_t | vsg::bvec4 |
| ub | unsigned byte | std::uint8_t | vsg::ubvec4 |
| s | signed short | std::int16_t | vsg::svec2 |
| us | unsigned short | std::uint16_t | vsg::usvec2 |
| i | signed int | std::int32_t | vsg::vec3 |
| ui | unsigned int | std::uint32_t | vsg::uivec3 |

All the maths types are simple structs, only containing the data fields required for the type and are not subclassed from vsg::Object like other scene graph objects as their focus in representing low level data and supporting maths operations. All math types can all be used as part of data objects which will cover in the next page - [Data Types](DataTypes.md).The available types are and the headers that define them are follow.

Vector, quaternion & plane types:
* vsg::vec2 [include/vsg/maths/vec2.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec2.h)
* vsg::vec3 [include/vsg/maths/vec3.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec3.h)
* vsg::vec4 [include/vsg/maths/vec4.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec4.h)
* vsg::quat [include/vsg/maths/quat.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/quat.h)

Matrix types:
* vsg::mat3 [include/vsg/maths/mat3.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat3.h)
* vsg::mat4 [include/vsg/maths/mat4.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat4.h)

Geometric primitive types:
* vsg::plane [include/vsg/maths/plane.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/plane.h)
* vsg::sphere [include/vsg/maths/sphere.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/sphere.h)
* vsg::box [include/vsg/maths/sphere.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/box.h)

## Vectors

The vsg::vec* types provide GLSL style access, with {x,y,z,w} & {r,g,b,a} and [] accessors which all map to the same underlying numerical values.

## Quaternion

The vsg::quat types provide GLSL style access, with {x,y,z,w} and [] accessors which all map to the same underlying numerical values.

## Matrices


## Geometric primtives


---

Prev: [vsg::observer_ptr](observer_ptr.md)| Next: [Data Tpes](DataTypes.md)
