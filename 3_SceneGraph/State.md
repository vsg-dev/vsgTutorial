---
layout: page
title: State
permalink: /scenegraph/State
---

The class definitions for the Vulkan state nodes of the scene graph can bound found the [VulkanSceneGraph/include/vsg/state](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) directory.

## Scene graph state nodes

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::StateCommand | [StateCommand.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | Base class for state commands - binding pipelines & descriptors |
| vsg::StateGroup | [StateGroup.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/StateGroup.h) | State group node that provides a list of StateCommands to decorate a subgraph |
| vsg::Light | [Light.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Light.h) | Light node provides all the settings for positing and controlling the type, color of a light source |

## State commands

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::BindComputePipeline | [ComputePipeline.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| vsg::BindGraphicsPipeline | [GraphicsPipeline.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| vsg::BindDescriptorSet | [BindDescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| vsg::PushConstants | [PushConstants.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| vsg::StateSwitch | [StateSwitch.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |

## Shaders, Descriptor and Pipeline layout

| Class | Header | Functionality |
| --- | --- | --- |
| | [ShaderModule.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [ShaderStage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [DescriptorSetLayout.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [PipelineLayout.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |


## Graphics pipeline state

| Class | Header | Functionality |
| --- | --- | --- |
| | [ColorBlendState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [DepthStencilState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [InputAssemblyState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [DynamicState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [MultisampleState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [RasterizationState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [TessellationState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [VertexInputState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [ViewportState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |

## Descriptor state

| Class | Header | Functionality |
| --- | --- | --- |
| | [BindDescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [DescriptorSetLayout.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [Descriptor.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [DescriptorBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [Buffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [BufferInfo.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [BufferView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [Sampler.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [DescriptorImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [DescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [DescriptorTexelBufferView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [Image.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [ImageInfo.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [ImageView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [material.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [QueryPool.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |

## General support classes

| Class | Header | Functionality |
| --- | --- | --- |
| | [ResourceHints.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [ArrayState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |
| | [ViewDependentState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | |

Prev: [Commands](Commands.md)| Next : [Mesh Shaders](MeshShaders.md)

