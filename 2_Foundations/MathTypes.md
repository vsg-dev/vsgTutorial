---
layout: page
title: Maths Types
permalink: /foundations/MathsTypes
---

The VulkanSceneGraph provides GLSL style vector, quaternion and matrix types which are used both to represent data that can be used to store data on the CPU and can be directly mapped to GPU memory for use by shaders, and provides range of standard vector math functions.  We'll discuss the [math functions](MathFunctions.md) later in this chapter, this page will discuss the data types.

The math data types are found in the [include/vsg/maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/) directory. All the types are declared as template<> structs with definitions provided for the specific types supporting bool, 8, 16 and 32 bit int and unsigned ints, float and double versions of each type.

Simple structs are used, only containing the data fields required for the type and are not subclassed from vsg::Object like other scene graph objects as their focus in representing low level data and supporting maths operations. All math types can all be used as part of data objects which will cover in the next page - [Data Types](DataTypes.md).The available types are and the headers that define them are follow.

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

The prefix of the type describes the numerical type, the mappings are:

| Prefix | Description | Type | Example |
| no prefix | 32 bit floating point | float | vsg::vec3 |
| d | 64 bit floating point | double | vsg::dmat4 |
| b | signed byte | std::int8_t | vsg::bvec4 |
| ub | unsigned byte | std::uint8_t | vsg::ubvec4 |
| s | signed short | std::int16_t | vsg::svec2 |
| us | unsigned short | std::uint16_t | vsg::usvec2 |
| i | signed int | std::int32_t | vsg::vec3 |
| ui | unsigned int | std::uint32_t | vsg::uivec3 |

## Vectors

The vsg::vec* types provide GLSL style access, with {x,y,z,w} & {r,g,b,a} and [] accessors which all map to the same underlying numerical values. All the vector types also support set(..) methods and assignment. The vector types have a range uses and the accessors used support these:

~~~ cpp
// vertices and normals
vsg::dvec3 position{1.0, 2.0, 3.0); // double vec3
position.x = 1.0; // equivalent to position[0] = 1.0
position[1] = 2.0; // equivalent to position.y = 2.0

vsg::vec3 normal(0.0f, 0.0f, 1.0f); // floating point vec3
normal.set(0.0f, 1.0f, 0.0f);

// colours
vsg::vec4 color(1.0f, 0.0f, 0.0f, 1.0f); // float vec4 representing opqaue red
color.r *= 0.5f; // half the red intensity
color[3] = 1.0f; // set the b channel to 1.0

vsg::ubvec4 packed_color(0, 255, 0, 127)l // unsigned byte semi-transparent green
packed_color = vsg::ubvec4(255, 255, 255, 255); // assign an all white color

// you can use .x, .r & [0] etc. access interchangeably
std::cout<<"color : red = "<<color[0]<<", green = "<<color.g<<", blue = "<<color.z<<", alpha = "<<color.a<<std::endl;
~~~

## Quaternion

The vsg::quat types provide GLSL style access, with {x,y,z,w} and [] accessors which all map to the same underlying numerical values.

## Matrices


## Geometric primtives


---

Prev: [vsg::observer_ptr](observer_ptr.md)| Next: [Data Tpes](DataTypes.md)
