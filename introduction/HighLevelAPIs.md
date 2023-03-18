---
layout: page
title: High Level APIs
permalink: /introduction/HighLevelAPIs
---

Developers wishing to add graphics capabilities to their applications have to either deal directly with the low APIs to drive the graphics and compute hardware, or choose from a collection of higher level APIs that are more focused on the needs of application developers than the underlying low level APIs. A good high level APIs will not only enable developer to be more productive but also provide better out of the box performance and visual quality, with the high level API packaging up the expertise and time put in by specialist in high performance graphics and compute.

High level APIs may choose to remain quite minimal in feature set and leave more functionality for the application developer to implement, while others bring in many different areas of functionality. They may also be written to be general purposes through to domain specific such as certain genre's of games.

Some high level APIs choose to build in low level API abstraction layers so they can support multiple APIs such as Vulkan, OpenGL, multiple versions of Direct3D, Metal etc - this brings us to the perverse realm of the hardware abstraction abstraction layer. Such extra abstraction layers adds cpmplexity and move the application developer further away from what they are attempting to run on the hardware. This approach also adds more code for the high level API maintainer to write, test, debug and support, and far greater range of perumtatins of hardware and APIs to test and support.  This poor engineeering approach has been born from the real or periecved issues with how well the cross platform low level APIs are supported across platforms, it's a workaround to the attempts of Microsoft/Apple/etc. to excert vendor lock-in.

An alterantive approach used by some high level APIs is to simply encapsulate the low level APIs rather than abstract from them, this keeps the application developer closer to a 1:1 relationship with the data and processing they managing on the hardware. Taking this path could limit pprtabilitiy to particular OSs, or hardware, but thankfully with OpenGL and Vulkan they are designed to be both OS nmagnostic and capable of handling a wide range of hardware so the chose to encapsualte OpenGL or Vulkan need not limit portablity over the low level API abstraction approach.

## A Brief history of high level APIs

One of the first widely used high level APIs for real-time 3D graphics was IRIS Inventor that was started at SGI in the late 1980's and follows a scene graph approach for respresent a 3d scene.  Created to make development of 3D graphics applications easier as the lowl level nature of IRIS GL was a barrier to entry.  Successsed by Open Inventor which adopts OpenGL as it's base and became widely adopted in the scientific and engineering sectors where ease of use was more critical than maximzing performance.  Inventor's strength lay in it's Object Orientatioed Design and use of the Scene Graph as as a way of composing a scene, it's weakness was in the way it's design limits performance and scalaibility.

---


Prev: [Low Level APIs](LowLevelAPIs.md) | Next: [Vulkan](Vulkan.md)
