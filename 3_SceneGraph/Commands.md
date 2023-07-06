---
layout: page
title: Commands
permalink: /scenegraph/Commands
---

The class definitions for the Vulkan command nodes of the scene graph can bound found the [VulkanSceneGraph/include/vsg/commands](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) directory.

| Class | Header | Functionality |
| ----------------- | ----------------- | ----------------- |
| vsg::Compileable | [Compilable.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Compilable.h) | Base class for objects that can be compiled |
| vsg::Command | [Command.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Command.h) | Base class for vkCmd* types|
| vsg::Commands | [Commands.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Commands.h) | Group of vsg::Command |


| Class | Header | Functionality |
| ----------------- | ----------------- | ----------------- |
| vsg::BindIndexBuffer | [BindIndexBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BindIndexBuffer.h) | [vkCmdBindIndexBuffer](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdBindIndexBuffer.html) |
| vsg::BindVertexBuffers | [BindVertexBuffers.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BindVertexBuffers) | [vkCmdBindVertexBuffers](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdBindVertexBuffers.html) |


| Class | Header | Functionality |
| ----------------- | ----------------- | ----------------- |
| vsg::Draw | [Draw.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Draw.h) | [vkDraw](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDraw.html) |
| vsg::DrawIndexed | [DrawIndexed.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/DrawIndexed.h) | [vkDrawIndexed](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDrawIndexed.html) |
| vsg::DrawIndexedIndirect | [DrawIndexedIndirect.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/DrawIndexedIndirect.h) | [vkCmdDrawIndexedIndirect](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDrawIndexedIndirect.html) |
| vsg::DrawIndirectCommand | [DrawIndirectCommand.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/DrawIndirectCommand.h) | [vkCmdDrawIndirectCommand](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDrawIndexedIndirectCommand.html) |
| vsg::DrawIndirect | [DrawIndirect.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/DrawIndirect.h) | [vkCmdDrawIndirect](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDrawIndirect.html) |


| Class | Header | Functionality |
| vsg::CopyImage | [CopyImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/CopyImage.h) | |
| vsg::CopyImageToBuffer | [CopyImageToBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/CopyImageToBuffer.h) | |
| vsg::CopyImageViewToWindow | [CopyImageViewToWindow.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/CopyImageViewToWindow.h) | |
| vsg::CopyQueryPoolResults | [CopyQueryPoolResults.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/CopyQueryPoolResults.h) | |
| vsg::CopyAndReleaseBuffer | [CopyAndReleaseBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/CopyAndReleaseBuffer.h) | |


| Class | Header | Functionality |
| vsg::BlitImage | [BlitImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BlitImage.h) | |
| vsg::ResolveImage | [ResolveImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/ResolveImage.h) | |


| Class | Header | Functionality |
| vsg::Dispatch | [Dispatch.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Dispatch.h) | |


| Class | Header | Functionality |
| vsg::Event | [Event.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Event.h) | |
| vsg::PipelineBarrier | [PipelineBarrier.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/PipelineBarrier.h) | |


| Class | Header | Functionality |
| vsg::ClearAttachments | [ClearAttachments.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/ClearAttachments.h) | |
| vsg::ExecuteCommands | [ExecuteCommands.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/ExecuteCommands.h) | |
| vsg::NextSubPass | [NextSubPass.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/NextSubPass.h) | |


| Class | Header | Functionality |
| vsg::SetDepthBias | [SetDepthBias.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/SetDepthBias.h) | |
| vsg::SetLineWidth | [SetLineWidth.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/SetLineWidth.h) | |
| vsg::SetScissor | [SetScissor.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/SetScissor.h) | |
| vsg::SetViewport | [SetViewport.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/SetViewport.h) | |


| Class | Header | Functionality |
| vsg::BeginQuery | [BeginQuery.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BeginQuery.h) | |
| vsg::EndQuery | [EndQuery.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/EndQuery.h) | |
| vsg::ResetQueryPool | [ResetQueryPool.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/ResetQueryPool.h) | |
| vsg::WriteTimestamp | [WriteTimestamp.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/WriteTimestamp.h) | |

Prev: [Nodes](Nodes.md)| Next: [State](State.md)

