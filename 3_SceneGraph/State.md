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
| vsg::ColorBlendState | [ColorBlendState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ColorBlendState.h) | Settings for [VkPipelineColorBlendStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineColorBlendStateCreateInfo.html) |
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
| vsg::BindDescriptorSet | [BindDescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/BindDescriptorSet.h) | |
| vsg::DescriptorSetLayout | [DescriptorSetLayout.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorSetLayout.h) | |
| vsg::Descriptor | [Descriptor.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/Descriptor.h) | |
| vsg::DescriptorBuffer | [DescriptorBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorBuffer.h) | |
| vsg::Buffer | [Buffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/Buffer.h) | |
| vsg::BufferInfo | [BufferInfo.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/BufferInfo.h) | |
| vsg::BufferView | [BufferView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/BufferView.h) | |
| vsg::Sampler | [Sampler.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/Sampler.h) | |
| vsg::DescriptorImage | [DescriptorImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorImage.h) | |
| vsg::DescriptorSet | [DescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorSet.h) | |
| vsg::DescriptorTexelBufferView | [DescriptorTexelBufferView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorTexelBufferView.h) | |
| vsg::Image | [Image.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/Image.h) | |
| vsg::ImageInfo | [ImageInfo.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ImageInfo.h) | |
| vsg::ImageView.| [ImageView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ImageView.h) | |
| vsg::material | [material.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/material.h) | Material vsg::Data types |
| vsg::QueryPool | [QueryPool.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/QueryPool.h) | |

## General support classes

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::ResourceHints etc. | [ResourceHints.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ResourceHints.h) | Resource requirement hints |
| vsg::ArrayState etc. | [ArrayState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ArrayState.h) | vsg::ArrayState base class for mapping vertex shader behavior on CPU |
| vsg::ViewDependentState etc. | [ViewDependentState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ViewDependentState.h) | View dependent state classes |

Prev: [Commands](Commands.md)| Next : [Mesh Shaders](MeshShaders.md)

