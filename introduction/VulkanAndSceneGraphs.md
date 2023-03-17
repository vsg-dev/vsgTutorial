---
layout: page
title: Introduction to Vulkan and Scene Graphs
permalink: /introduction/VulkanAndSceneGraphs
---

TODO - write about Vulkan and Scene Graphs

# Low level APIs for graphics and compute

In 1992 SGI introduced OpenGL - cross platform C API capable of rendering textured triangles and basic lighting.  In early nineties SGI and OpenGL saw massive adoption and growth.

In 1996 Mirosoft introduced Direct3D - new era of vendor lock-in, while early rev's weren't competitive to OpenGL that the industry sleeped walked/coerced into adoption.

Early 2000 Direct3D dominats games industry, OpenGL left serving professional graphics applicaitons.

In August 2009 OpenCL is launched by Apply and in 2010 was adopted by Khronos Group as a cross-vendor Compute on GPU API to work compliment OpenGLs Graphics on GPU capabilities.

In 2013 AMD started working on Mantle to develop an API with much lower overhead and better able to maximize utilization of modern multi-core CPUs and super fast GPUs.

In 2014 Apple joins the vendor lock-in game, after supporting OpenGL creates it's onw low level Metal API, begins march towards deprecating OpenGL on Apple systems.

Khnoros adopts Mantle as the basis for cross-vendor, cross platform successor to OpenGL, eventially releaseing the Vulkan-1.0 spec in February 2016.

In Feb. 2018 MoltenVK library is released enabling Vulkan to run ontop of Metal on macOS and iOS systems breaking the vendor lock-in and enabling Vulkan to work on all major hardware and software platforms.

---

# High level APIs for graphics and compute.


---

 | Next: [Introduction to the VulkanSceneGraph project](VulkanSceneGraphProject.md)
