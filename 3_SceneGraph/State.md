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
| vsg::BindComputePipeline | [ComputePipeline.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ComputePipeline.h) | Bind the compute pipeline |
| vsg::BindGraphicsPipeline | [GraphicsPipeline.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/GraphicsPipeline.h) | Bind the graphics pipeline |
| vsg::BindDescriptorSet | [BindDescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/BindDescriptorSet.h) | Bind descriptors sets to current pipelin |
| vsg::PushConstants | [PushConstants.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/PushConstants.h) |  apply push constants using vkPushConstants |
| vsg::StateSwitch | [StateSwitch.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/StateSwitch.h) | applies child state commands which pass mask test |

## Shaders, Descriptor and Pipeline layout

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::ShaderModule | [ShaderModule.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ShaderModule.h) | Settings for vkShaderModule |
| vsg::ShaderStage | [ShaderStage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ShaderStage.h) | Settings for vkShaderStage |
| vsg::DescriptorSetLayout | [DescriptorSetLayout.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorSetLayout.h) | Settings for descriptor set layout |
| vsg::PipelineLayout | [PipelineLayout.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/PipelineLayout.h) | Settings for pipeline layout |

## Graphics pipeline state

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::ColorBlendState | [ColorBlendState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ColorBlendState.h) | |
| vsg::DepthStencilState | [DepthStencilState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DepthStencilState.h) | |
| vsg::InputAssemblyState| [InputAssemblyState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/InputAssemblyState.h) | |
| vsg::DynamicState | [DynamicState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DynamicState.h) | |
| vsg::MultisampleState | [MultisampleState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/MultisampleState.h) | |
| vsg::RasterizationState | [RasterizationState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/RasterizationState.h) | |
| vsg::TessellationState | [TessellationState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/TessellationState.h) | |
| vsg::VertexInputState | [VertexInputState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/VertexInputState.h) | |
| vsg::ViewportState| [ViewportState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ViewportState.h) | |

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

