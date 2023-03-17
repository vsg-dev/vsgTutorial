---
layout: page
title: Introduction to Vulkan and Scene Graphs
permalink: /introduction/VulkanAndSceneGraphs
---

# A Brif Hstory of low level APIs for graphics and compute

In the 1980's SGI created it's IRIS GL (https://en.wikipedia.org/wiki/IRIS_GL) anC API for 2D and 3D rendering on SGI hardware.

In 1992 SGI introduced OpenGL - an open and cross platform C API capable of rendering textured triangles and basic lighting on a variaty.  In early nineties SGI and OpenGL saw massive adoption and growth/

In 1996 Microsoft introduced Direct3D - new era of vendor lock-in, while early rev's weren't competitive to OpenGL, the industry sleeped walked/coerced into adoption by Microsoft anti-competitive practices.

Early 2000 Direct3D dominats games industry, OpenGL left serving professional graphics applicaitons.

In August 2009 [OpenCL](https://en.wikipedia.org/wiki/OpenCL) is launched by Apply and in 2010 was adopted by Khronos Group as a cross-vendor Compute on GPU API to work compliment OpenGLs Graphics on GPU capabilities.

In 2013 AMD started working on [Mantle](https://en.wikipedia.org/wiki/Mantle_(API)) to develop an API with much lower overhead and better able to maximize utilization of modern multi-core CPUs and super fast GPUs.

In 2014, after many years of supporting OpenGL, Apple joins the vendor lock-in game, creating it's own low level [Metal API](https://en.wikipedia.org/wiki/Metal_(API)), begins march towards deprecating OpenGL on Apple systems.

Khnoros adopts Mantle as the basis for a new cross-vendor, cross platform successor to OpenGL, releaseing the [Vulkan-1.0](https://en.wikipedia.org/wiki/Vulkan) spec in February 2016. Vulkan is lower level than OpenGL, applications take over more responisiblities that previously OpenGL drivers would have to manage, but provides more freedom and control over data and mulit-threaded control of data and commands being passed to/from the GPU. Vulkan ombines Compute and Graphics in one single coherent API.

In Feb. 2018 MoltenVK library is released enabling Vulkan to run ontop of Metal on macOS and iOS systems breaking the vendor lock-in and enabling Vulkan to work on all major hardware and software platforms.

---

# High level APIs for graphics and compute.

One of the first widely used high level APIs for real-time 3D graphics was IRIS Inventor that was started at SGI in the late 1980's.  Created to make development of 3D graphics applications easier as the lowl level nature of IRIS GL was a barrier to entry.  Successsed by Open Inventor which adopts OpenGL as it's base and became widely adopted in the scientific and engineering sectors where ease of use was more critical than maximzing performance.

---

 | Next: [Introduction to the VulkanSceneGraph project](VulkanSceneGraphProject.md)
