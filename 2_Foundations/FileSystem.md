---
layout: page
title: File System features
permalink: /foundations/FileSystem
---

C++17 in theory has almost full support for all the file system related functionality that VulkanSceneGraph and it's user will need, but unfortunately compiler support for all the std::filesystem features across all platforms was too patchy to rely upon.  To address this definciancy the VulkanSceneGraph provides this functionality to ensure the same experience across all platforms and compatibility with older compiler,

## vsg::Path

The [std::filesystem::path](https://en.cppreference.com/w/cpp/filesystem/path) class equivalent in the [vsg::Path](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/Path.h#L37) class. This broadly mirrors functionality focusing on the key functionality required by the VulkanSceneGraph and it's users.

# file system functions

The file system functions are group together in the [include/vsg/io/FileSystem.h](https://github.com/vsg-dev/VulkanSceneGraph/tree/master/include/vsg/io/FileSystem.h#L37) header.

Prev: [Serialization](Serialization.md) | Next : [StreamsAndLogger](StreamsAndLogger.md)

