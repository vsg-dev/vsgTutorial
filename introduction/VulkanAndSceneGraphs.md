---
layout: page
title: Introduction to Vulkan and Scene Graphs
permalink: /introduction/VulkanAndSceneGraphs
---

## Low level APIs for graphics and compute

Low level graphics and compute APIs provide an interface with hardware drivers that manage data transfers and processing on highly parallised graphics and compute hardware. Low level APIs may be tied to specific operatings systems and/or specific sets of hardware, through to being capable of running on multiple operation systems and across a wide range of hardware.  OpenGL and Vulkan are examples of the later that are OS agnostic and provide extensible hardware abstraction.

Low level APIs focus in interfacing with hardware efficiently, rather than making it convenient to develop graphics and compute applications. Older low level APIs like OpenGL provide higher level of abstraction than modern low level APIs like Vulkan and Direct2D 12, which are designed to enable greater low level control over data, processing and synchronization with the hardware.  These modern APIs can be seen as more focused on hardware performance and capabilities than on supporting the needs of application developers, so while lifting the ceiling on raw performance and quality they require greater knowledge and skill from application developers in order to use them - just rendering a textured triangle can take 1,500 lines of code!


## A Brief History of low level APIs

In the 1980's SGI created it's IRIS GL (https://en.wikipedia.org/wiki/IRIS_GL) anC API for 2D and 3D rendering on SGI hardware.

In 1992 SGI introduced OpenGL - an open and cross platform C API capable of rendering textured triangles and basic lighting on a variaty.  In early nineties SGI and OpenGL saw massive adoption and growth/

In 1996 Microsoft introduced Direct3D - new era of vendor lock-in, while early rev's weren't competitive to OpenGL, the industry slept walked/coerced into adoption by Microsoft anti-competitive practices.

Early 2000 Direct3D dominats games industry, OpenGL left serving professional graphics applications.

In August 2009 [OpenCL](https://en.wikipedia.org/wiki/OpenCL) is launched by Apply and in 2010 was adopted by Khronos Group as a cross-vendor Compute on GPU API to work compliment OpenGLs Graphics on GPU capabilities.

In 2013 AMD started working on [Mantle](https://en.wikipedia.org/wiki/Mantle_(API)) to develop an API with much lower overhead and better able to maximize utilization of modern multi-core CPUs and super fast GPUs.

In 2014, after many years of supporting OpenGL, Apple joins the vendor lock-in game, creating it's own low level [Metal API](https://en.wikipedia.org/wiki/Metal_(API)), begins march towards deprecating OpenGL on Apple systems.

Khnoros adopts Mantle as the basis for a new cross-vendor, cross platform successor to OpenGL, releaseing the [Vulkan-1.0](https://en.wikipedia.org/wiki/Vulkan) spec in February 2016. Vulkan is lower level than OpenGL, applications take over more responisiblities that previously OpenGL drivers would have to manage, but provides more freedom and control over data and mulit-threaded control of data and commands being passed to/from the GPU. Vulkan ombines Compute and Graphics in one single coherent API.

In Feb. 2018 MoltenVK library is released enabling Vulkan to run on top of Metal on macOS and iOS systems breaking the vendor lock-in and enabling Vulkan to work on all major hardware and software platforms.

## Vulkan - next generation graphics and compute API that provides high-efficiency

Useful websites:

* [vulkan.org](https://www.vulkan.org/) - official website
    * Learning:
        * [Key Resources](https://www.vulkan.org/learn#key-resources)
        * [Tuotorials](https://www.vulkan.org/learn#vulkan-tutorials)
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

* [VulkanSDK](https://vulkan.lunarg.com/sdk/home) LUNARG's website containing the VulkanSDK -
provides single package with headers and libs for Windows, Linux and macOS.

* [AndroidNDK](https://developer.android.com/ndk/guides/graphics/index.html) - Googles Android NDK

* [Vulkan on Wikipedia](https://en.wikipedia.org/wiki/Vulkan) mentions the platforms supported by Vulkan:
 "Vulkan runs natively on Android, Linux, BSD Unix, QNX, Haiku, Nintendo Switch, Raspberry Pi, Stadia, Fuchsia, Tizen, and Windows 7, 8, 10, and 11. MoltenVK provides freely-licensed third-party support for macOS, iOS and tvOS by wrapping over Apple's Metal API."

---

## High level APIs for graphics and compute.

Developers wishing to add graphics capabilities to their applications have to either deal directly with the low APIs to drive the graphics and compute hardware, or choose from a collection of higher level APIs that are more focused on the needs of application developers than the underlying low level APIs. A best high level APIs will not only enable developer to be more productive but also provide better out of the box performance and visual quality, with the high level API packaging up the expertise and time put in by specialist in high performance graphics and compute.

High level APIs may choose to remain quite minimal in feature set and leave more functionality for the application developer to implement, while others bring in many different areas of functionality. They may also be written to be general purposes through to domain specific such as certain genre's of games.

Some high level APIs choose to build in low level API abstraction layers so they can support multiple APIs such as Vulkan, OpenGL, multiple versions of Direct3D, Metal etc - this brings us to the perverse realm of the hardware abstraction abstraction layer. Such extra abstraction layers adds cpmplexity and move the application developer further away from what they are attempting to run on the hardware. This approach also adds more code for the high level API maintainer to write, test, debug and support, and far greater range of perumtatins of hardware and APIs to test and support.  This poor engineeering approach has been born from the real or periecved issues with how well the cross platform low level APIs are supported across platforms, it's a workaround to the attempts of Microsoft/Apple/etc. to excert vendor lock-in.

An alterantive approach used by some high level APIs is to simply encapsulate the low level APIs rather than abstract from them, this keeps the application developer closer to a 1:1 relationship with the data and processing they managing on the hardware. Taking this path could limit pprtabilitiy to particular OSs, or hardware, but thankfully with OpenGL and Vulkan they are designed to be both OS nmagnostic and capable of handling a wide range of hardware so the chose to encapsualte OpenGL or Vulkan need not limit portablity over the low level API abstraction approach.

## A Brief history of high level APIs

One of the first widely used high level APIs for real-time 3D graphics was IRIS Inventor that was started at SGI in the late 1980's.  Created to make development of 3D graphics applications easier as the lowl level nature of IRIS GL was a barrier to entry.  Successsed by Open Inventor which adopts OpenGL as it's base and became widely adopted in the scientific and engineering sectors where ease of use was more critical than maximzing performance.  Inventor strength lay in it's Object Orientatioed Design and use of the Scene Graph as as a way of composing a scene.

---

 | Next: [Introduction to the VulkanSceneGraph project](VulkanSceneGraphProject.md)
