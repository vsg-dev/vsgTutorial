---
layout: page
title: Scene Graph
permalink: /scenegraph/
---

At the heart of the VulkanSceneGraph is classes that make up the scene graph, all the classes and features discused in the Foundations chapter provide the base from which these scene graph classes are built, and the subsequent chapter on application will provide the higher level integration to present the scene graph. This chapter will walk readers through the internal nodes of the scene graph, the commands that are recorded in Vulkan command buffers to do the work on the GPU, and the state that is used by those commands.

1. [Nodes](Nodes.md) - internal nodes of the scene graph
2. [Commands](Commands.md) - Vulkan commands for doing operations on the GPU such as draw calls and compute dispatch
3. [State](State.md) - Vulkan state for setting data and programs on the GPU such as shaders, textures, uniforms
