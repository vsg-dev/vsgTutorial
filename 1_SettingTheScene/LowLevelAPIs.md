---
layout: page
title: Low-level APIs
permalink: /SettingTheScene/LowLevelAPIs
---

Low-level graphics and compute APIs provide an interface with hardware drivers that manage data transfers and processing on highly parallelized graphics and compute hardware.  Low-level APIs may be tied to specific operating systems and/or specific sets of hardware, through to being capable of running on multiple operating systems and across a wide range of hardware.  OpenGL and Vulkan are examples of the latter that are OS agnostic and provide extensible hardware abstraction.

### Level of Hardware Abstraction vs Complexity

Low-level APIs focus on interfacing with hardware efficiently, rather than making it convenient to develop graphics and compute applications.  Older low-level APIs like OpenGL provide a higher level of abstraction than modern low-level APIs like Vulkan and Direct3D 12, which are designed to enable greater low-level control over data, processing and synchronization with the hardware.

These modern APIs can be seen as more focused on hardware performance and capabilities than on supporting the needs of application developers, so while lifting the ceiling on raw performance and quality they require significantly greater expertise from application developers in order to use them.

### Incremental vs Monolithic

OpenGL and Vulkan are written to evolve incrementally and in a fine grained way, with vendor specific extensions being exposed before these features are worked on by groups of vendors and before these features eventually are merged into the core.  This contrasts with a monolithic approach taken by Direct3D with major versions changing the API and features exposed, to use the latest features you have no choice but to update to the new API version.

For applications that will be developed over many years the approach taken with OpenGL and Vulkan helps keep the applications relevant without requiring major rewrites as new features can be introduced one by one as software & hardware evolves.  The discrete jumps of Direct3D would require major rewrites in order to take advantage of new features, not a major issue for application types like games that get written once and have a short shelf life, but would be a hindrance for long lived applications.

## A Brief History of low-level APIs

In the 1980's SGI created IRIS GL (https://en.wikipedia.org/wiki/IRIS_GL), a C API for 2D and 3D rendering on SGI hardware.

In 1992 SGI introduced OpenGL - an open and cross platform C API capable of rendering textured triangles and basic lighting on a variety of hardware and OS's.  Throughout the early nineties SGI and OpenGL saw massive adoption and growth for both OpenGL and SGI as a company.

In 1996 Microsoft introduced Direct3D - starting a new era of vendor lock-in, while early rev's weren't competitive to OpenGL, the industry sleepwalked into adoption by Microsoft's anti-competitive practices.

During the early 2000s Direct3D progressively dominated the games industry, with OpenGL left serving professional graphics applications.

In August 2009 [OpenCL](https://en.wikipedia.org/wiki/OpenCL) was launched by Apple and in 2010 it was adopted by Khronos Group as a cross-vendor Compute on GPU API to complement OpenGL's Graphics on GPU capabilities.

In 2013 AMD started working on [Mantle](https://en.wikipedia.org/wiki/Mantle_(API)) to develop an API with much lower overhead that was better able to maximize utilization of modern multi-core CPUs and super fast GPUs.

In 2014, after many years of supporting OpenGL, Apple joined the vendor lock-in game, creating its own low-level [Metal API](https://en.wikipedia.org/wiki/Metal_(API)), and began a march towards deprecating OpenGL on Apple systems.

Khronos adopted Mantle as the basis for a new cross-vendor, cross platform successor to OpenGL, releasing the [Vulkan-1.0](https://en.wikipedia.org/wiki/Vulkan) spec in February 2016.  Vulkan is lower level than OpenGL, applications take over more responsibilities that previously OpenGL drivers would have had to manage, but provides more freedom and control, such as multi-threaded control of data and commands being passed to/from the GPU.  Vulkan combines Compute and Graphics in one single coherent API.

In February 2018 the MoltenVK library was released enabling Vulkan to run on top of Metal on macOS and iOS systems breaking the vendor lock-in and enabling Vulkan to work on all major hardware and software platforms.

---

Prev: [Introduction](index.md) | Next: [Vulkan](Vulkan.md)
