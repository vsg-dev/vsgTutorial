---
layout: page
title: VulkanSceneGraph Library
permalink: /introduction/VulkanSceneGraphLibrary
---

The [VulkanSceneGraph library](https://github.com/vsg-dev/VulkanSceneGraph/) provides the features that will be common to all graphics & compute applications - creating a viewer, windows, scene graph, reading/writing data, creating Vulkan objects and recording Vulkan commands, synchronizing with Vulkan processes and CPU threads, 3d vector maths and common utilities like computing bounds and intersection test and shader composition and cmpilation. 

## Feature organization

All VulkanSceneGraph projects follow the same structure - public headers can be found in include/ directories and the implementation can be found in the src/ directories. This pattern is used to make it clear to end users what part of they will interface with, and as clear demarcation to library developers & contributors that interfaces and implementations both have clear and distinct roles. When installing the software it'll only the files in the include directories and any built libraries + cmake config files that will be installed.

The [vsg library headers](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg) are grouped in the following [include/vsg](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/) subdirectories:

Foundational class directories:
* [core](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/core) - base classes, smart pointer, data continers, allocators and visitor base classes
* [maths](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/maths) - GLSL style maths classes, similar to glm
* [io](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io) - serialization and built-in reader/writers.

Scene graph class directories:
* [commands](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/commands) - scene graph nodes for Vulkan Commands
* [state](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/state) - scene graph objects for setting Vulkan state.
* [nodes](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/) - scene graph nodes like groups, swtiches & transforms
* [text](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/text) - text scene graph nodes
* [meshshaders](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/meshshaders) - Khronos Mesh Shader support
* [raytracing](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/raytracing) - Khronos Ray Tracing support

Application class directories:
* [vk](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/vk) - high level Vulkan integration such vkInstance/vkDevice etc.
* [app](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/app) - application level Vulkan classes
* [platform](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/platform) - platform specific Windowing support
* [ui](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/ui) - user interface classes such as mouse and keyboard events
* [utils](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/utils) - collection of utilities such intersections through to shader composition and compilation.
* [threading](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/threading) - threading classes and helper functions

The sections of the vsgTutorial are grouped in this way so as you work through you'll be introduced to [Foundational](../foundations.md), [Scene Graph](../scenegraph.md) and [Application](../application.md) areas in turn.

## Naming conventions

All VulkanSceneGraph projects use the following naming convnetions:

| **Project** | **Library** | **Namespace** | **CMake package**|
| VulkanSceneGraph | vsg | vsg:: | find_package(vsg) |
| vsgXchange | vsgXchange | vsgXchange:: | find_package(vsgXchange) |
| vsgImGui | vsgImGui | vsgImGui:: | find_package(vsgImGui) |
| vsgQt | vsgQt | vsgQt:: | find_package(vsgQt) |

All Vulkan related classes in the VulkanSceneGraph follow the naming conventions vkFeatureName -> vsg::FeatureName, for example:

| **Vulkan** | **VulkanSceneGraph** |
| vkInstance | vsg::Instance |
| vkPhysicalDevice | vsg::PhysicalDevice | 
| vkDevice | vsg::Device |
| vkFramebuffer | vsg::Framebuffer |
| vkSurface | vsg::Surface |

The class and variable naming conventions is predominatly CamelCase but as there are cases where we use snake_case. If a function/template or struct mirrors a Standard C++ feature then snake_case may be used.  For the GLSL inspired math support structs are used and have a leading lower case letter i.e. vsg::vec3 and vsg::mat4.

## Public vs Protected/Private scope and naming convention:

Classes in the VulkanSceneGraph predominatly follow the declaration of scope in order of public interface through to internal implementation details. The naming of public members variables and methods follow camelCase while protected and private members variables and methods are prefixed with a _ so that their roles can be seen in the declaration and implementation.  

For the same reasons that headers and source files are kept in distinct include and src directories, this convention is used to make it clear to end users and to implementers that public facing variables and methods are special, as users will set, get and call them their naming and types need to be more refined and maintained over time. While the protected and private members are implementation deatils that may be more subject to change.

~~~ C++

class MyClass
{
public:
    bool enabled = true;
    void publicMethod();

protected:
    int _count = 0;
    void _protectedMethod();

private:
    float _forDevelopersOnly = 1;
};

~~~

Where data members can vary independently those members are simply declared in the public scope and can be set directly, this mirrors Vulkan CreateInfo structs used to set up Vulkan objects, as well as keeping the usage easy to use and the code base clean and minimal.  This coherence with Vulkan also means it's easier to reuse Vulkan documentation.

~~~ C++
class KeepItSimple
{
public:
    std::string name;
    float value;
};
~~~

For cases where data members do not vary independently a protected or private member is used and access is managed through public methods:

~~~ C++
class AnotherClass
{
public:
    void setValue(float v) { _value = v; ++_modifiedCount; }
    float getValue() const { return _value = v;}

    int getModifiedCount() { return _modifiedCount; }

protected:
    float _value = 0.0f;
    int _modifiedCount = 0;
};

---

 Prev: [VulkanSceneGraph Project](VulkanSceneGraphProject.md)| Next: [Building VulkanSceneGraph projeects and exercises](BuildingVulkanSceneGraph.md)
