#ifndef __ENGINE_COMMAND_BUFFER__
#define __ENGINE_COMMAND_BUFFER__

#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include <array>
#include "Model.hpp"
#include "PointeurClass.hpp"

namespace Ge
{
    class CommandBuffer
    {
    private:
        friend class RenderingEngine;
        bool initialize(VulkanMisc * vM, ptrClass * ptrC);
        void release();
    private:
        VulkanMisc * vulkanM;
		std::vector<VkCommandBuffer> m_commandBuffers;
    };
}

#endif //__ENGINE_COMMAND_BUFFER__