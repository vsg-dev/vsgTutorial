---
layout: page
title: VulkanSceneGraph Ecosystem
permalink: /SettingTheScene/Ecosystem
---

One of the weaknesses of the OpenSceneGraph project is that, while it started as a small scene graph library, step by step it encompassed a wider range of features and dependencies. While the OpenSceneGraph stops short of providing all the functionality of a Game Engine it is bloated for the needs of many application developers.  Early in the VulkanSceneGraph project the decision was made to create an ecosystem built on a general purpose scene graph library and a collection of companion libraries each focused on specific features that users can easily compile and use in their applications if they need them.

## Foundation for all VulkanSceneGraph applications

Features that all applications developers using Vulkan will need, so provided by the VulkanSceneGraph library:
* robustly create and cleanup data
* serialization of scene graph objects to native ascii and binary file formats
* extensible mechanism for reading/writing 3rd party data.
* vector math classes and associated functions
* robust management of the lifetime of Vulkan objects including support for Vulkan extensions
* scene graph internal nodes, state and geometry
* creation and management of Vulkan capable windows, offscreen buffers and event handling
* support for views, cameras and control of them
* support for commonly used graphics pipelines - flat shaded, phong and physics based rendering

## Ecosystem centred around vsg-dev GitHub account

The [vsg-dev](https://github.com/vsg-dev) GitHub account hosts the following projects which are officially supported as part the VulkanSceneGraph project, the three main projects that the majority of developers will need to use are:
* [VulkanSceneGraph](https://github.com/vsg-dev/VulkanSceneGraph) - The VulkanSceneGraph library itself is capable of being used on its own for standalone graphics applications, and for embedded platforms this may be the desired approach as it will minimize the code base that needs to be QA'd for security and robustness, and minimizes the final executable size.
* [vsgXchange](https://github.com/vsg-dev/vsgXchange)
It is expected that for most desktop applications, users will also want to load a range of 2D image and 3D model data, to support this usage the library adds support for a wide range of image and 3D model formats, using assimp, as well as support for reading data from http/https using libcurl, and reading/writing/processing of GIS imagery and DEMS through the optional GDAL integration.
* [vsgExamples](https://github.com/vsg-dev/vsgExamples)
A collection of 59 examples (as of 20th March 2023) that have been written to help test VulkanSceneGraph features as they are developed and as an educational tool for new users.

Also hosted on vsg-dev are more specialized projects:

* [osg2vsg](https://github.com/vsg-dev/osg2vsg) - osg2vsg library for converting data and integrating OpenGL/OSG and Vulkan/VSG applications. vsgXchange will automatically add support for reading data using the OpenSceneGraph's loader when osg2vsg has been built and installed before vsgXchange.
* [vsgImGui](https://github.com/vsg-dev/vsgImGui) - ImGui and ImPlot integration with the VulkanSceneGraph
* [vsgQt](https://github.com/vsg-dev/vsgQt) - Qt5/Qt6 integration with the VulkanSceneGraph
* [vsgPoints](https://github.com/vsg-dev/vsgPoints) 3d point cloud loading and rendering for VulkanSceneGraph.
* [vsgUnity](https://github.com/vsg-dev/vsgUnity) - plugin for the Unity Editor for exporting VulkanSceneGraph models
* [MyFirstVsgApplication](https://github.com/vsg-dev/MyFirstVsgApplication) - simple standalone example illustrating the CMake and C++ code required for a basic application.
* [vsgFramework](https://github.com/vsg-dev/vsgFramework) - template project that uses CMake FetchContent to pull in all the main libraries associated with VulkanSceneGraph and its dependencies and builds them together.

## Community projects:
* [vsgSDL](https://github.com/ptrfun/vsgSDL) SDL integration with VulkanSceneGraph.
* [vsgvr](https://github.com/geefr/vsgvr) OpenVR integration with VulkanSceneGraph.
* [vsgCs](https://github.com/timoore/vsgCs) 3D Tiles and Cesium ion integration
* [vsgEarth](https://github.com/timoore/vsgEarth) osgEarth integration

## 3rd party dependencies

The VulkanSceneGraph library uses Vulkan, C++17 and CMake as external dependencies. The Vulkan C headers are used rather than the Vulkan C++ header which is unnecessary as the VulkanSceneGraph provides its own encapsulation of Vulkan objects in a way that is consistent with how they are used in the scene graph.

For runtime shader compilation support the [glslang](https://github.com/KhronosGroup/glslang) library is used, originally as an optional external dependency, but since VulkanSceneGraph-1.0.3 it is now built internally as a submodule, this is compiled in by default but can be toggled off by setting the CMake VSG_SUPPORTS_ShaderCompiler variable to 0 before building the source. Compiling glslang within the VulkanSceneGraph library resolved problems with inconsistent 3rd party packaging of glslang, so now users can have a seamless experience across platforms.

The additional VulkanSceneGraph projects add their own dependencies:

| Project | Required | Optional |
| [VulkanSceneGraph](https://github.com/vsg-dev/VulkanSceneGraph) | C++17, CMake, Vulkan | glslang integrated as a submodule |
| [vsgXchange](https://github.com/vsg-dev/vsgXchange) | VulkanSceneGraph | curl, assimp, gdal, freetype, OpenEXR, osg2vsg |
| [vsgImGui](https://github.com/vsg-dev/vsgImGui) | VulkanScenegraph, ImGui & ImPlot integrated as a submodule | |
| [vsgQt](https://github.com/vsg-dev/vsgQt) | VulkanSceneGraph, Qt5.10 or later, Qt6 | |
| [vsgPoints](https://github.com/vsg-dev/vsgPoints) | VulkanSceneGraph |  |
| [vsgExamples](https://github.com/vsg-dev/vsgExamples) | VulkanSceneGraph | vsgXchange, vsgImGui |

---

 Prev: [Performance Principles](PerformancePrinciples.md)| Next: [VulkanSceneGraph Library](VulkanSceneGraphLibrary.md)
