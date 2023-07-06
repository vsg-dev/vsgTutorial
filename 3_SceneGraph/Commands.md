---
layout: page
title: Commands
permalink: /scenegraph/Commands
---

The class definitions for the Vulkan command nodes of the scene graph can bound found the [VulkanSceneGraph/include/vsg/commands](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) directory.

| Class | Header | Functionality |
| vsg::Compileable | [Compilable.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/nodes/Compilable.h) | Base class for objects that can be compiled |
| vsg::Command | [Command.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Command.h) | Base calss for vkCmd* types|
| vsg::Commands | [Commands.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/Commands.h) | Group of vsg::Command |


| vsg::BindIndexBuffer | [BindIndexBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BindIndexBuffer.h) | [vkCmdBindIndexBuffer](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdBindIndexBuffer.html) |
| vsg::BindVertexBuffers | [BindVertexBuffers.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BindVertexBuffers) | [vkCmdBindVertexBuffers](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdBindVertexBuffers.html) |

| vsg::Draw | [Draw.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | [vkDraw](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDraw.html) |
| vsg::DrawIndexed | [DrawIndexed.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | [vkDrawIndexed](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDrawIndexed.html) |
| vsg::DrawIndexedIndirect | [DrawIndexedIndirect.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | [vkCmdDrawIndexedIndirect](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDrawIndexedIndirect.html) |
| vsg::DrawIndirectCommand | [DrawIndirectCommand.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | [vkCmdDrawIndirectCommand](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkDrawIndexedIndirectCommand.html) |
| vsg::DrawIndirect | [DrawIndirect.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | [vkCmdDrawIndirect](https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/vkCmdDrawIndirect.html) |


| vsg::CopyImage | [CopyImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::CopyImageToBuffer | [CopyImageToBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::CopyImageViewToWindow | [CopyImageViewToWindow.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::CopyQueryPoolResults | [CopyQueryPoolResults.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::CopyAndReleaseBuffer | [CopyAndReleaseBuffer.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |


| vsg::BlitImage | [BlitImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::ResolveImage | [ResolveImage.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |


| vsg::Dispatch | [Dispatch.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |


| vsg::Event | [Event.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::PipelineBarrier | [PipelineBarrier.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |


| vsg::ClearAttachments | [ClearAttachments.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::ExecuteCommands | [ExecuteCommands.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::NextSubPass | [NextSubPass.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |


| vsg::SetDepthBias | [SetDepthBias.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::SetLineWidth | [SetLineWidth.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::SetScissor | [SetScissor.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::SetViewport | [SetViewport.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |


| vsg::BeginQuery | [BeginQuery.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/BeginQuery.h) | |
| vsg::EndQuery | [EndQuery.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::ResetQueryPool | [ResetQueryPool.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |
| vsg::WriteTimestamp | [WriteTimestamp.h](https://github.com/vsg-dev/VulkanSceneGraph/blob/master/include/vsg/commands/) | |

Prev: [Nodes](Nodes.md)| Next: [State](State.md)

