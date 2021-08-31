#ifndef __ENGINE_COMMAND_BUFFER__
#define __ENGINE_COMMAND_BUFFER__

#include "VulkanMisc.hpp"

namespace Ge
{
    class CommandBuffer
    {
    private:
        friend class RenderingEngine;
        bool initialize(VulkanMisc * vM);
        void release();
    private:
        VulkanMisc * vulkanM;
    };
}

#endif //__ENGINE_COMMAND_BUFFER__