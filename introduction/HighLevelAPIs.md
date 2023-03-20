---
layout: page
title: High Level APIs
permalink: /introduction/HighLevelAPIs
---

Developers wishing to add graphics capabilities to their applications have to either deal directly with the low APIs to drive the graphics and compute hardware, or choose from a collection of higher level APIs that are more focused on the needs of application developers than the underlying low level APIs. A good high level APIs will not only enable developer to be more productive but also provide better out of the box performance and visual quality, with the high level API packaging up the expertise and time put in by specialists in high performance graphics and compute.

### Scene Graphs

A common concept utilized by high level graphics APIs is a Scene Graph. Scene Graphs are an example of Directed Acylic Graph (DAG), where a tree like hierarchy is used to rerepsent the scene.  Nodes in the graph made be internal group nodes, support culling like view frustum or level of detail culling, through to behavior like switches or sequences, or represent state or geometries that are passed GPU for rendering.

### Features vs Generality

High level APIs may choose to remain quite minimal in feature set and leave more functionality for the application developer to implement, while others build in many different areas of functionality. Broadly speaking the wider the range features provided by an API the more domain specific it becomes as each additional feature will choose a particular approach or 3rd party dependency that are likely to work well for some domains more than others. The more features bundled together the more feature choices are made for you and more likely they'll be inappropriate for your needs or provide bloat from features you'll never need. The advantage of the graeter feature integration is potentially providing a cohessive system of features that work well together.

An example of high level API with relatively modest feature set and tight focus would be scene graph like Open Inventor or Performer, while one that encompass a extensive feature set would a game engine like Unreal or Unity. These two approaches aren't incompatible - a game engine could contain it's own scene graph or a 3rd party scene graph, the later approach was taken by [Delta3D](https://en.wikipedia.org/wiki/Delta3D) project that built upon the OpenSceneGraph.


### Abstraction vs Encapslation

Some high level APIs choose to build in low level API abstraction layers so they can support multiple APIs such as Vulkan, OpenGL, multiple versions of Direct3D, Metal etc - this brings us to the perverse realm of the hardware abstraction abstraction layer. Such extra abstraction layers adds cpmplexity and move the application developer further away from what they are attempting to run on the hardware. This approach also adds more code for the high level API maintainer to write, test, debug and support, and far greater range of perumtatins of hardware and APIs to test and support.  This poor engineeering approach has been born from the real or periecved issues with how well the cross platform low level APIs are supported across platforms, it's a workaround to the attempts of Microsoft/Apple/etc. to excert vendor lock-in.

An alternative approach used by some high level APIs is to simply encapsulate the low level APIs rather than abstract from them, this keeps the application developer closer to a 1:1 relationship with the data and processing they managing on the hardware. Taking this path could limit pprtabilitiy to particular OSs, or hardware, but thankfully with OpenGL and Vulkan they are designed to be both OS nmagnostic and capable of handling a wide range of hardware so the chose to encapsualte OpenGL or Vulkan need not limit portablity over the low level API abstraction approach.

## A Brief history of high level APIs

One of the first widely used high level APIs for real-time 3D graphics was IRIS [Inventor](https://en.wikipedia.org/wiki/Open_Inventor) that was started at SGI in the late 1980's and follows a scene graph approach for respresent a 3d scene.  Created to make development of 3D graphics applications easier as the lowl level nature of IRIS GL was a barrier to entry.  Successsed by Open Inventor which adopts OpenGL as it's base and became widely adopted in the scientific and engineering sectors where ease of use was more critical than maximzing performance.  Inventor's strength lay it's embodiment of the scene grah concept in such a flexibility and extensibility way. It's weakness was in the way it's design limited performance and scalaibility.

[Performer](https://en.wikipedia.org/wiki/OpenGL_Performer) created in 1991 by developers from the Inventor development group to focus on performance rather than usability. Performer was designed to work muli-threaded working on multiple CPU and mulitple GPU's in order to scale to utilize SGI's high end hardware such as the Onyx line of graphics "super" computers. These have far less perfromance and capabilities than modern phones, but during the mid 90's they were worlds most powerful graphics systems.

[Cosmo3D](https://en.wikipedia.org/wiki/OpenGL%2B%2B) - mid 1990's yet another SGI scene graph! Created to provide a unified scene graph that was scalable and high performance like perfromer, and better usuability like Inventor. SGI worked with other vendors to create a statndardised OepnGL++ scene graph, using Cosmo3D as the base.

[Farenheight](https://en.wikipedia.org/wiki/Fahrenheit_(graphics_API)) - late 1990's. SGI and Microsoft colloboration to create a low level API successpr to OpenGL, and high level successor to Inventor/Performer. High level used a Cosmo3D as starting place.  Mcrisoft strung SGI along for a year before the project collapsed, with Microsoft using the IP agreement to enabled more advancd features to make it into Direct3D. Microsoft's plan all along?

The collapse of the Farenheight project left a vecum in the world of standardized high level APIs, the proprittary scene graph had failed to deliver a standardized solution as had been done for low level APIs. In the late 1990's Open Sourc/Free Software was growing in significance and offered an entirely different approach to creating software, a number of hobby level proejcts sprung up like [Plib](https://sourceforge.net/projects/plib/) through to [CystalSpace](https://en.wikipedia.org/wiki/Crystal_Space) but none had anything close to capabilities of the profressional APIs like Inventor, Performaner and other propritary APIs like Vega.

In 1999 the Fraunhofer Institute created a consortium to develop [OpenSG](https://en.wikipedia.org/wiki/OpenSG) project, from the outset it had high asperations for delivering am Open Soucrce cross platform, scalable, high performance scene graph - embracing all the facets that the industry had been wanting from Farenheight.

At the same time, completely indepdently and intially unware of OpenSG project, Don Burns, an SGI engineer, working in his spare time on a home built Hang Gliding Simulator created a small scene graph library, ontop ontop OpenGL, simply because Performer hadn't yet been ported to the Linux PC yet. Don sought assistance from Robert Osfield, fellow software engineer and Hang Glider pilot but with knowledge of aredyanmics, in to help with the development of the flight model. Robert ported the nascent scene graph library to Windows and the decision was made to publish the library as Opn Source under the LGPL license.  Originally named SG, for Scene Graph, Open was added to name and the [OpenSceneGraph](https://en.wikipedia.org/wiki/OpenSceneGraph) proejct came into existance with a tar.gz file published on a single webs page.  Two engineers in their spare time hacking away on a hang glider sim with no lofty goal beyond just getting a hang glider, a flying site with a hill and a few trees rendered.

In 2000 the vis-sim and GIS sectors desperately needed a modern, professional grade graphics scene graph alternative to the propritary scene graph projects were poorly supported, slow moving or failing. OpenSG and OpenSceneGraph both were contenders but paradoxically the grand plans of the OpenSG project meant it's release cycle was too slow for the industry desperate for a new scene graph, while the OpenSceneGraph developed in spare time, with no formal plans or funding but a rapid release cycle and responsive lead develolpers gained acceptance in the vis-sim and GIS sector. By 2001 the OpenSceneGarph had gained a commercial following sufficient for Robert then Don to leave their full-time jobs and go fultime and pay the bills through consulting, bespoke development work and training services.

---


Prev: [Low Level APIs](LowLevelAPIs.md) | Next: [Vulkan](Vulkan.md)
