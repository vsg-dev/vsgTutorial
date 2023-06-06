---
layout: page
title: Maths Functions
permalink: /foundations/MathsFunctions
---

The VulkanSceneGraph maths types and functions are found in the [include/vsg/maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/) directory. The conventions broadly follow GLSL conventions with additions that are helpful for scene graph usage.  In the [Math Types] (MathTypes.md) section, earlier in this chapter, the vec2, vec3, vec4, mat3, mat4, quat, plane, box and sphere classes were introduced. In this section we build upon this with tour of the range of helper functions available and an explanation of the conventions used.

## Conventions

The VulkanSceneGraph follows the GLSL convention of [Right Hand Rule](https://en.wikipedia.org/wiki/Right-hand_rule) and [Column Major](https://en.wikipedia.org/wiki/Row-_and_column-major_order) matrices. The GLSL conventions are followed to make it easier to move code between shaders and C++ code, and to make it easier to follow 3rd party coding examples.


## Difference with OpenSceneGraph conventions

The use of column major contrats that of the OpenSceneGraph that uses row major, this not only affects order for access elements of matrices but also the transformation order you'll use. The row major convention used by the OpenSceneGraph was adopted prior to the existance of GLSL which unfortunately chose the opposite convention, leaving the OpenSceneGraph in an awkawrd situation where C++ and shaders follow differing convnetions.

~~~ cpp
// OpenSceneGraph use row major
osg::Vec3d osg_vec;
osg::Matrixd osg_matrix;
osg_matrix(row, column) = value;
osg::Vec3d osg_dash = osg_vec * matrix;

// VulkanSceneGraph using GLSL column major convention
vsg::dvec3 vsg_vec;
vsg::dmat4 vsg_matrix;
vsg_matrix(column, row) = value;
vsg::dvec3 vsg_dask = matrix * vsg_vec
~~~

## Headers and associated types/functionality

| header | types |
| --- | --- |
| *vector and quaternion* | |
| [include/vsg/maths/vec2.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec2.h) | vsg::vec2 |
| [include/vsg/maths/vec3.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec3.h) | vsg::vec3 |
| [include/vsg/maths/vec4.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec4.h) | vsg::vec4 |
| [include/vsg/maths/quat.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/quat.h) | vsg::quat |
| *matrix types* | |
| [include/vsg/maths/mat3.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat3.h) | vsg::mat3 |
| [include/vsg/maths/mat4.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat4.h) | vsg::mat3 |
| *geometric primitive types* | |
| [include/vsg/maths/plane.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/plane.h) | vsg::plane |
| [include/vsg/maths/sphere.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/sphere.h) | vsg::sphere |
| [include/vsg/maths/sphere.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/box.h) | vsg::box |
| *functions* | |
| [include/vsg/maths/clamp.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/clamp.h) | clamp and repeat texture coord style functions |
| [include/vsg/maths/color.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/color.h) | color helper functions |
| [include/vsg/maths/common.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/common.h) | angle, square, smoothstep and mix helper functions |
| [include/vsg/maths/sample.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/sample.h) | sample function equvilant to GPU texture sampler |
| [include/vsg/maths/transform.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/transform.h) | range of transform related functions |

---

Prev: [Block memory management with vsg::Allocator](Allocator.md)| Next : [Next Chapter : Scene Graph](../3_SceneGraph/index.md)
