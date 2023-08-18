---
layout: page
title: Maths Types
permalink: /foundations/MathsTypes
---

The VulkanSceneGraph provides GLSL style vector, quaternion and matrix types which are used both to represent data that can be used to store data on the CPU and can be directly mapped to GPU memory for use by shaders, and provides range of standard vector math functions. We'll discuss the [Math Functions](MathFunctions.md) later in this chapter, this page will discuss the data types.

The math data types are found in the [include/vsg/maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/) directory. All the types are declared as template<> structs with definitions provided for the specific types, supporting bool, 8, 16 and 32 bit int and unsigned ints, float and double versions of each type.

Simple structs are used, only containing the data fields required for the type and are not subclassed from vsg::Object like other scene graph objects as their focus in representing low level data and supporting maths operations. All math types can all be used as part of data objects which we will cover in the next page - [Data Types](DataTypes.md).

## Available types and the associated headers

Vector & quaternion:
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
* vsg::box [include/vsg/maths/box.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/box.h)

## Prefix naming convention

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

The [vsg::vec2](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec2.h), [vec3](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec3.h), [vec4](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec4.h) types provide GLSL style access, with {x,y,z,w}, {r,g,b,a}, {s,t,p,q} and [] accessors which all map to the same underlying numerical values. All the vector types also support set(..) methods and assignment. The vector types have a range uses and the accessors used support these:

~~~ cpp
// double precision position, good for GIS on CPU
vsg::dvec3 position{1.0, 2.0, 3.0);
position.x = 1.0; // equivalent to position[0] = 1.0
position.y = 2.0; // equivalent to position[1] = 2.0

// float vertex, good for GPU work
vsg::vec3 vertex{1.0f, 2.0f, 3.0f);
vertex.x = 1.0f; // equivalent to position[0] = 1.0f
vertex[1] = 2.0f; // equivalent to position.y = 2.0f

// float normals
vsg::vec3 normal(0.0f, 0.0f, 1.0f); // floating point vec3
normal.set(0.0f, 1.0f, 0.0f);

// colours
vsg::vec4 color(1.0f, 0.0f, 0.0f, 1.0f); // float vec4 representing opaque red
color.r *= 0.5f; // half the red intensity
color[3] = 1.0f; // set the a channel to 1.0

vsg::ubvec4 packed_color(0, 255, 0, 127); // unsigned byte semi-transparent green
packed_color = vsg::ubvec4(255, 255, 255, 255); // assign an all white color

// you can use .x, .r & [0] etc. access interchangeably
std::cout<<"color : red = "<<color[0]<<", green = "<<color.g<<", blue = "<<color.z<<", alpha = "<<color.a<<std::endl;
std::cout<<"number of components : color.size() = "<<color.size()<<std::endl; // will be 4 for vec4 types
~~~

## Quaternion

The [vsg::quat](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/quat.h) type is a rotation, defined in [quaternion](https://en.wikipedia.org/wiki/Quaternion) form, that provides {x,y,z,w} and [] accessors which all map to the same underlying numerical values:

~~~ cpp
// double precision quaternion useful for defining rotations, useful for GIS etc. applications
// use the angle, axis constructor to create a 90 degree rotation about the z axis.
vsg::dquat rotation(vsg::radians(90.0), vsg::dvec3(0.0, 0.0, 1.0));

std::cout<<"rotation = "<<rotation.x<<", "<<rotation.y<<", "<<rotation.z<<", "<<rotation.w<<std::endl;

// default constructed single precision quaternion represents non rotation
vsg::quat rot;

// set as a rotation between two vectors
rot.set(vsg::vec3(1.0f, 0.0f, 0.0f),  vsg::vec3(0.0f, 1.0f, 0.0f));

// the quat::size() method returns 4
std::cout<<"rot = ";
for(size_t i=0; i<rot.size(); ++i) std::cout<<" "<<rot[i]<<std::endl;

~~~

## Matrices

The [vsg::mat3](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat3.h), [mat4](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat4.h) types provide GLSL style access, with [element] & [column][row] accessors which all map to the same underlying numerical values. The vector types have a range uses and the accessors used support these:

~~~ cpp
// single precision 3x3 matrix useful for rotation
vsg::mat3 rotation_matrix(1.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 1.0f);

// double precision 4x4 matrix useful for homogeneous transformations
// default constructed provides an identity matrix.
vsg::dmat4 matrix;

// set the translation of 100, 200, 300 units.
matrix[3][0] = 100.0;
matrix[3][1] = 200.0;
matrix[3][2] = 300.0;
~~~

## Geometric primitives

The [vsg::plane](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/plane.h), [sphere](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/sphere.h) and [box](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/box.h) types do not have a direct GLSL equivalent but are very useful for geometric primitives that are used in graphics applications. The conventions used follow the same patterns as used in the vector, quaternion and matrix types.

~~~ cpp

// define a single precision horizontal plane at height of 1 unit
vsg::plane pl(0.0f, 0.0, 1.0f, -1.0f);

// create unit cube polytope from planes
std::vector<vsg::dplane> poltope = {
    {1.0, 0.0, 0.0, 1.0}, // left plane at x=-1, pointing right
    {-1.0, 0.0, 0.0, 1.0}, // right plane at x=1, pointing left
    {0.0, 1.0, 0.0, 1.0}, // front plane at y=-1, pointing forward
    {0.0, -1.0, 0.0, 1.0}, // back plane at y=1, pointing backward
    {0.0, 0.0, 1.0, 1.0}, // bottom plane at z=-1, pointing upwards
    {0.0, 0.0, -1.0, 1.0} // top plane at z=1, pointing downwards
};

// double precision sphere at {10, 20, 30) with radius of 40 units
vsg::dsphere bounding_sphere(10.0, 20.0, 30.0, 40.0);

// default constructed single precision box representing an undefined box
// bounding_box.min is set to maximum float values.
// bounding_box.max is set to minimum float values.
// when min.x value > max.x then box is treated as undefined/invalid/empty.
vsg::box bounding_box;

// use the vsg::box::add(..) method to compute the bounding box that encloses points
bounding_box.add(vsg::vec3(0.0f, 0.0f, 0.0f));
bounding_box.add(vsg::vec3(10.0f, 0.0f, 0.0f));
bounding_box.add(vsg::vec3(0.0f, 5.0f, 0.0f));
bounding_box.add(vsg::vec3(0.0f, 6.0f, 3.0f));

std::cout<<"bounding_box min = ("<<bounding_box.min<<"), max = ("<<bounding_box.max<<")"<<std::endl;
~~~

---

Prev: [vsg::observer_ptr](observer_ptr.md)| Next: [Data Tpes](DataTypes.md)
