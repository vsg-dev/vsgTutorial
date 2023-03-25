---
layout: page
title: Vulkan - graphics and compute API
permalink: /SettingTheScene/Vulkan
---

The standards body [Khronos](https://www.khronos.org/) releases, the successor to OpenGL, Vulkan-1.0 in February 2016, ushering in next generation of Open, Cross Platform API for graphics and compute.

### Pros:
* Very low CPU overhead enables low power consumption and higher performance.

* Multi-threaded for modern CPUs and GPUs:
Designed from the ground up for multi-threading, with localization of state within command buffers that applications thread create to explicit synchronization primitives for managing CPU and GPU work.

* Cross platform: [source Wikipedia](https://en.wikipedia.org/wiki/Vulkan)
"Vulkan runs natively on Android, Linux, BSD Unix, QNX, Haiku, Nintendo Switch, Raspberry Pi, Stadia, Fuchsia, Tizen, and Windows 7, 8, 10, and 11. MoltenVK provides freely-licensed third-party support for macOS, iOS and tvOS by wrapping over Apple's Metal API."

* Runtime extension system, enabling fine grainded support for latest hardware features, including:
    * Ray Tracing
    * Mesh Shaders

* Vulkan layers that can be enabled at runtime
    * Validation layers
    * API output layers
    * Best practice guides

### Cons:

* Low level, responsibility for many tasks moves from driver into application scope.
Developers must explicitly configure settings, allocate and manage memory, transferring of data to/from GPU, dispatching and synchronizing CPU and GPU operations.

* Requires more knowledge and code to implement even simple features - 1,500 lines of code to just render a textured triangle!

### Useful links:

* [VulkanSDK](https://vulkan.lunarg.com/sdk/home) LUNARG's website containing the VulkanSDK -
provides single package with headers and libs for Windows, Linux and macOS.

* [AndroidNDK](https://developer.android.com/ndk/guides/graphics/index.html) - Googles Android NDK

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
    * [Vulkan-SC](https://www.khronos.org/vulkansc/) Vulkan for safety-critical systems

---

Prev: [Low Level APIs](LowLevelAPIs.md) | Next :[High Level APIs](HighLevelAPIs.md)

