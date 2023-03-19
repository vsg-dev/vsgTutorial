---
layout: page
title: High Level APIs
permalink: /introduction/HighLevelAPIs
---

Developers wishing to add graphics capabilities to their applications have to either deal directly with the low APIs to drive the graphics and compute hardware, or choose from a collection of higher level APIs that are more focused on the needs of application developers than the underlying low level APIs. A good high level APIs will not only enable developer to be more productive but also provide better out of the box performance and visual quality, with the high level API packaging up the expertise and time put in by specialists in high performance graphics and compute.

A common concept utilized by high level graphics APIs is a Scene Graph. Scene Graphs are an example of Directed Acylic Graph (DAG), where a tree like hiearchy is used to rerepsent the scene.  Nodes in the graph made be internal group nodes, support culling like view frustum or level of detail culling, through to behavior like switches or sequences, or represent state or geometries that are passed GPU for rendering.

High level APIs may choose to remain quite minimal in feature set and leave more functionality for the application developer to implement, while others build in many different areas of functionality. Broadly speaking the wider the range features provided by an API the more domain specific it becomes as each additional feature will choose a particular approach or 3rd party dependency that are likely to work well for some domains more than others. The more features bundled together the more feature choices are made for you and more likely they'll be inappropriate for your needs or provide bloat from features you'll never need. The advantage of the graeter feature integration is potentially providing a cohessive system of features that work well together.

An example of high level API with relatively modest feature set and tight focus would be scene graph like Open Inventor or Performer, while one that encompass a extensive feature set would a game engine like Unreal or Unity. These two approaches aren't incompatible - a game engine could contain it's own scene graph or a 3rd party scene graph, the later approach was taken by [Delta3D](https://en.wikipedia.org/wiki/Delta3D) project that built upon the OpenSceneGraph.

Some high level APIs choose to build in low level API abstraction layers so they can support multiple APIs such as Vulkan, OpenGL, multiple versions of Direct3D, Metal etc - this brings us to the perverse realm of the hardware abstraction abstraction layer. Such extra abstraction layers adds cpmplexity and move the application developer further away from what they are attempting to run on the hardware. This approach also adds more code for the high level API maintainer to write, test, debug and support, and far greater range of perumtatins of hardware and APIs to test and support.  This poor engineeering approach has been born from the real or periecved issues with how well the cross platform low level APIs are supported across platforms, it's a workaround to the attempts of Microsoft/Apple/etc. to excert vendor lock-in.

An alterantive approach used by some high level APIs is to simply encapsulate the low level APIs rather than abstract from them, this keeps the application developer closer to a 1:1 relationship with the data and processing they managing on the hardware. Taking this path could limit pprtabilitiy to particular OSs, or hardware, but thankfully with OpenGL and Vulkan they are designed to be both OS nmagnostic and capable of handling a wide range of hardware so the chose to encapsualte OpenGL or Vulkan need not limit portablity over the low level API abstraction approach.

## A Brief history of high level APIs

One of the first widely used high level APIs for real-time 3D graphics was IRIS Inventor that was started at SGI in the late 1980's and follows a scene graph approach for respresent a 3d scene.  Created to make development of 3D graphics applications easier as the lowl level nature of IRIS GL was a barrier to entry.  Successsed by Open Inventor which adopts OpenGL as it's base and became widely adopted in the scientific and engineering sectors where ease of use was more critical than maximzing performance.  Inventor's strength lay it's embodiment of the scene grah concept in such a flexibility and extensibility way. It's weakness was in the way it's design limited performance and scalaibility.

---


Prev: [Low Level APIs](LowLevelAPIs.md) | Next: [Vulkan](Vulkan.md)
