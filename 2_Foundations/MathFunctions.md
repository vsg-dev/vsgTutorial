---
layout: page
title: Maths Functions
permalink: /foundations/MathsFunctions
---

The VulkanSceneGraph maths types and functions are found in the [include/vsg/maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/) directory. The conventions broadly follow GLSL conventions with additions that are helpful for scene graph usage.  In the [Math Types] (MathTypes.md) section, earlier in this chapter, the vec2, vec3, vec4, mat3, mat4, quat, plane, box and sphere classes were introduced. In this section we build upon this with tour of the range of helper functions available and an explanation of the conventions used.

## Convnetions

The VulkanSceneGraph follows the GLSL convention of [Right Hand Rule](https://en.wikipedia.org/wiki/Right-hand_rule) and [Column Major](https://en.wikipedia.org/wiki/Row-_and_column-major_order) matrices.

## Recap of availble types

| header | types |
| --- | --- |
| vector and quaternion | |
| [include/vsg/maths/vec2.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec2.h) | vsg::vec2 class  |
| [include/vsg/maths/vec3.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec3.h) | vsg::vec3 class  |
| [include/vsg/maths/vec4.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/vec4.h) | vsg::vec4 class  |
| [include/vsg/maths/quat.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/quat.h) | quaternion |
| matrices | |
| [include/vsg/maths/mat3.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat3.h) | vsg::mat3 |
| [include/vsg/maths/mat4.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/mat4.h) | vsg::mat3 |
| Geometric primitive types: | |
| [include/vsg/maths/plane.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/plane.h) | vsg::plane |
| [include/vsg/maths/sphere.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/sphere.h) | vsg::sphere |
| [include/vsg/maths/sphere.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/box.h) | vsg::box |

## Functions

| header | functionality |
| --- | --- |
| [include/vsg/maths/clamp.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/clamp.h) | clamp and repeat texture coord style functions |
| [include/vsg/maths/color.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/color.h) | color helper functions |
| [include/vsg/maths/common.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/common.h) | angle, square, smoothstep and mix helper functions |
| [include/vsg/maths/sample.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/sample.h) | sample function equvilant to GPU texture sampler |
| [include/vsg/maths/transform.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths/transform.h) | range of transform related functions |

---

Prev: [Block memory management with vsg::Allocator](Allocator.md)| Next : [Next Chapter : Scene Graph](../3_SceneGraph/index.md)
