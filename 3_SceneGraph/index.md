---
layout: page
title: Scene Graph
permalink: /scenegraph/
---

**Currently being written.**

At the heart of the VulkanSceneGraph is classes that make up the scene graph, all the classes and features discussed in the [Foundations](../2_Foundations/index.md) chapter provide the base from which these scene graph classes are built, and the subsequent [Application](../4_Application/index.md) chapter will provide the higher level integration to present the scene graph.  This chapter will walk readers through the internal nodes of the scene graph, the commands that are recorded in Vulkan command buffers to do the work on the GPU, and the state that is used by those commands.

1. [Nodes](Nodes.md) - internal nodes of the scene graph
2. [Commands](Commands.md) - Vulkan commands for operations on the GPU such as draw and compute
3. [State](State.md) - Vulkan state for setting data and programs on the GPU such as shaders, textures, uniforms
4. [Mesh Shaders](MeshShaders.md) - Vulkan mesh shader extensions nodes
5. [Ray Tracing](RayTracing.md) - Vulkan ray tracing extensions nodes
5. [osg2vsg](osg2vsg.md) - Porting between OpenSceneGraph and VulkanSceneGraph
