---
layout: page
title: Vulkan - next gen. graphics and compute API
permalink: /introduction/Vulkan
---

Multi-threaded for modern CPUs and GPUs:

    Designed from the ground up for multi-threading, with localization of state within command buffers that applications thread create to explict syncronization primitives for managing CPU and GPU work.


Cross platform: [source Wikipedia](https://en.wikipedia.org/wiki/Vulkan)

    "Vulkan runs natively on Android, Linux, BSD Unix, QNX, Haiku, Nintendo Switch, Raspberry Pi, Stadia, Fuchsia, Tizen, and Windows 7, 8, 10, and 11. MoltenVK provides freely-licensed third-party support for macOS, iOS and tvOS by wrapping over Apple's Metal API."
    
Supports latest hardware features, including:

    * Ray Tracing
    * Mesh Shaders

 Useful links:

 * [vulkan.org](https://www.vulkan.org/) - official website
    * Learning:
        * [Key Resources](https://www.vulkan.org/learn#key-resources)
        * [Tutorials](https://www.vulkan.org/learn#vulkan-tutorials)
        * [Videos](https://www.vulkan.org/learn#videos)
        * [Blogs](https://www.vulkan.org/blog)
    * Tools:
        * [Drivers]([https://www.vulkan.org/tools#vulkan-gpu-resources)
        * [SDK](https://www.vulkan.org/tools#download-these-essential-development-tools)
        * [Profilers and debuggers](https://www.vulkan.org/tools#profilers-and-debuggers)
        * [Frameworks](https://www.vulkan.org/tools#frameworks-and-helper-libraries) - includes VulkanSceneGraph :-)
        * [Profiles](https://www.vulkan.org/tools#vulkan-profiles)
    * [Events](https://www.vulkan.org/events)
    * [News](https://www.vulkan.org/news)
    * [Vulkan-SC](https://www.khronos.org/vulkansc/)  
Vulkan SC is a streamlined, deterministic, robust API based on Vulkan 1.2 that enables state-of-the-art GPU-accelerated graphics and computation to be deployed in safety-critical systems that are certified to meet industry functional safety standards.

* [VulkanSDK](https://vulkan.lunarg.com/sdk/home) LUNARG's website containing the VulkanSDK -
provides single package with headers and libs for Windows, Linux and macOS.

* [AndroidNDK](https://developer.android.com/ndk/guides/graphics/index.html) - Googles Android NDK


 | Next: [Introduction to the VulkanSceneGraph project](VulkanSceneGraph.md)
