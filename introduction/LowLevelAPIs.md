---
layout: page
title: Low Level APIs
permalink: /introduction/LowLevelAPIs
---

Low level graphics and compute APIs provide an interface with hardware drivers that manage data transfers and processing on highly parallised graphics and compute hardware. Low level APIs may be tied to specific operatings systems and/or specific sets of hardware, through to being capable of running on multiple operation systems and across a wide range of hardware.  OpenGL and Vulkan are examples of the later that are OS agnostic and provide extensible hardware abstraction.

### Level of Hardware Abstraction vs Complexity

Low level APIs focus in interfacing with hardware efficiently, rather than making it convenient to develop graphics and compute applications. Older low level APIs like OpenGL provide higher level of abstraction than modern low level APIs like Vulkan and Direct2D 12, which are designed to enable greater low level control over data, processing and synchronization with the hardware.

These modern APIs can be seen as more focused on hardware performance and capabilities than on supporting the needs of application developers, so while lifting the ceiling on raw performance and quality they require significantly greater expertise from application developers in order to use them.

### Incremental vs Monolythic

OpenGL and Vulkan are written to evolving incrementally and in a fine grained way, with vendor specific extensions being exposed before these features worked on my groups of vendors and before these features eventually are merged into the core. This contrasts with the Monolythic approach taken by Direct3D with major versions changing the API and features exposed, to use the latest features you have no choice but to update to the new API version.

For applications that will be developed over many years the aooroach taken with OpenGL and Vulkan helps keep the applications relevant without requiring major rewrites as new features can be introduced one by one as software & hardware evolves.  The descrete jumps of Direct3D would requite major rewrites in order to take advantage of new features, not a major issue for application types like games that get written once and have a short shelf life, but would be hindrance for long lived applications.

## A Brief History of low level APIs

In the 1980's SGI created it's IRIS GL (https://en.wikipedia.org/wiki/IRIS_GL) anC API for 2D and 3D rendering on SGI hardware.

In 1992 SGI introduced OpenGL - an open and cross platform C API capable of rendering textured triangles and basic lighting on a variaty.  In early nineties SGI and OpenGL saw massive adoption and growth/

In 1996 Microsoft introduced Direct3D - new era of vendor lock-in, while early rev's weren't competitive to OpenGL, the industry slept walked/coerced into adoption by Microsoft anti-competitive practices.

Early 2000 Direct3D dominats games industry, OpenGL left serving professional graphics applications.

In August 2009 [OpenCL](https://en.wikipedia.org/wiki/OpenCL) is launched by Apply and in 2010 was adopted by Khronos Group as a cross-vendor Compute on GPU API to work compliment OpenGLs Graphics on GPU capabilities.

In 2013 AMD started working on [Mantle](https://en.wikipedia.org/wiki/Mantle_(API)) to develop an API with much lower overhead and better able to maximize utilization of modern multi-core CPUs and super fast GPUs.

In 2014, after many years of supporting OpenGL, Apple joins the vendor lock-in game, creating it's own low level [Metal API](https://en.wikipedia.org/wiki/Metal_(API)), begins march towards deprecating OpenGL on Apple systems.

Khnoros adopts Mantle as the basis for a new cross-vendor, cross platform successor to OpenGL, releaseing the [Vulkan-1.0](https://en.wikipedia.org/wiki/Vulkan) spec in February 2016. Vulkan is lower level than OpenGL, applications take over more responisiblities that previously OpenGL drivers would have to manage, but provides more freedom and control over data and mulit-threaded control of data and commands being passed to/from the GPU. Vulkan combines Compute and Graphics in one single coherent API.

In Feb. 2018 MoltenVK library is released enabling Vulkan to run on top of Metal on macOS and iOS systems breaking the vendor lock-in and enabling Vulkan to work on all major hardware and software platforms.

---

Prev :[Introduction](../introduction.md) | Next :[Vulkan](Vulkan.md)
