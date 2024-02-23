---
layout: page
title: State
permalink: /scenegraph/State
---

The class definitions for the Vulkan state nodes of the scene graph can be found in the [VulkanSceneGraph/include/vsg/state](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) directory.  Examples that illustrate use of various state classes can be found in the [vsgExamples/examples/state](https://github.com/vsg-dev/vsgExamples/tree/master/examples/state) directory,

## Scene graph state nodes

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::StateCommand | [StateCommand.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/) | Base class for state commands - binding pipelines & descriptors |
| vsg::StateGroup | [StateGroup.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/StateGroup.h) | State group node that provides a list of StateCommands to decorate a subgraph |
| vsg::Light | [Light.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Light.h) | Light node provides all the settings for positioning a light source, and controlling its type and color |

## State commands

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::BindComputePipeline | [ComputePipeline.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ComputePipeline.h) | Bind the compute pipeline |
| vsg::BindGraphicsPipeline | [GraphicsPipeline.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/GraphicsPipeline.h) | Bind the graphics pipeline |
| vsg::BindDescriptorSet | [BindDescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/BindDescriptorSet.h) | Bind descriptor sets to current pipeline |
| vsg::PushConstants | [PushConstants.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/PushConstants.h) |  Apply push constants using vkCmdPushConstants |
| vsg::StateSwitch | [StateSwitch.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/StateSwitch.h) | applies child state commands which pass mask test |

## Shaders, Descriptor and Pipeline layout

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::ShaderModule etc. | [ShaderModule.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ShaderModule.h) | Settings for [vkShaderModule](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkShaderModuleCreateInfo.html) |
| vsg::ShaderStage | [ShaderStage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ShaderStage.h) | Settings for [vkShaderStage](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineShaderStageCreateInfo.html) |
| vsg::DescriptorSetLayout | [DescriptorSetLayout.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorSetLayout.h) | Settings for [VkDescriptorSetLayout](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSetLayoutCreateInfo.html) |
| vsg::PipelineLayout | [PipelineLayout.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/PipelineLayout.h) | Settings for [VkPipelineLayout](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineLayoutCreateInfo.html) |

## Graphics pipeline state

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::ColorBlendState | [ColorBlendState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ColorBlendState.h) | [VkPipelineColorBlendStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineColorBlendStateCreateInfo.html) |
| vsg::DepthStencilState | [DepthStencilState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DepthStencilState.h) | [VkPipelineDepthStencilStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineDepthStencilStateCreateInfo.html)|
| vsg::InputAssemblyState| [InputAssemblyState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/InputAssemblyState.h) | [VkPipelineInputAssemblyStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineInputAssemblyStateCreateInfo.html) |
| vsg::DynamicState | [DynamicState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DynamicState.h) | [VkPipelineDynamicStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineDynamicStateCreateInfo.html) |
| vsg::MultisampleState | [MultisampleState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/MultisampleState.h) | [VkPipelineMultisampleStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineMultisampleStateCreateInfo.html) |
| vsg::RasterizationState | [RasterizationState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/RasterizationState.h) | [VkPipelineRasterizationStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineRasterizationStateCreateInfo.html) |
| vsg::TessellationState | [TessellationState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/TessellationState.h) | [VkPipelineTessellationStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineTessellationStateCreateInfo.html) |
| vsg::VertexInputState | [VertexInputState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/VertexInputState.h) | [VkPipelineVertexInputStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineVertexInputStateCreateInfo.html) |
| vsg::ViewportState| [ViewportState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ViewportState.h) | [VkPipelineViewportStateCreateInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkPipelineViewportStateCreateInfo.html) |

## Descriptor state

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::BindDescriptorSet etc. | [BindDescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/BindDescriptorSet.h) | Encapsulates [vkCmdBindDescriptors](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdBindDescriptorSets.html) |
| vsg::DescriptorSet | [DescriptorSet.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorSet.h) | Encapsulates [VkDescriptorSet](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorSetAllocateInfo.html)|
| vsg::Descriptor | [Descriptor.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/Descriptor.h) | Base class for [Descriptors](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkWriteDescriptorSet.html) |
| vsg::DescriptorBuffer | [DescriptorBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorBuffer.h) | Encapsulates [VkWriteDescriptorSet.pBufferInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkWriteDescriptorSet.html) |
| vsg::DescriptorImage | [DescriptorImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorImage.h) | Encapsulates [VkWriteDescriptorSet.pImageInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkWriteDescriptorSet.html) |
| vsg::DescriptorTexelBufferView | [DescriptorTexelBufferView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/DescriptorTexelBufferView.h) | Encapsulates [VkWriteDescriptorSet.pTexelBufferViews](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkWriteDescriptorSet.html) |
| vsg::Buffer | [Buffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/Buffer.h) | Encapsulates [VkBuffer](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferCreateInfo.html) |
| vsg::material | [material.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/material.h) | Material vsg::Data types |
| vsg::BufferInfo | [BufferInfo.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/BufferInfo.h) | Encapsulates [VkDescriptorBufferInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorBufferInfo.html) |
| vsg::BufferView | [BufferView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/BufferView.h) | Encapsulates [VkBufferView](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkBufferViewCreateInfo.html) |
| vsg::Sampler | [Sampler.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/Sampler.h) | Encapsulates [VkSampler](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkSamplerCreateInfo.html) |
| vsg::Image | [Image.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/Image.h) | Encapsulation of [VkImage](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageCreateInfo.html) |
| vsg::ImageView | [ImageView.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ImageView.h) | Encapsulation of [VkImageView](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkImageViewCreateInfo.html) |
| vsg::ImageInfo | [ImageInfo.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ImageInfo.h) | Encapsulates [VkDescriptorImageInfo](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDescriptorImageInfo.html) |

## General support classes

| Class | Header | Functionality |
| --- | --- | --- |
| vsg::ResourceHints etc. | [ResourceHints.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ResourceHints.h) | Hints that can be assigned to a scene graph as user data to specify the GPU resources required. |
| vsg::ArrayState etc. | [ArrayState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ArrayState.h) | vsg::ArrayState base class for mapping vertex shader behavior on CPU |
| vsg::ViewDependentState etc. | [ViewDependentState.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/ViewDependentState.h) | View dependent state classes |
| vsg::QueryPool | [QueryPool.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/state/QueryPool.h) | Encapsulates VkQueryPool, used with vsg::BeginQuery etc. |

Prev: [Commands](Commands.md)| Next: [Mesh Shaders](MeshShaders.md)

