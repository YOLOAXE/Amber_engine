#include "CommmandBuffer.hpp"

namespace Ge
{
    class CommandBuffer
    {
        bool initialize(VulkanMisc * vM)
        {
            vulkanM = vM;
        }
        void release();
    };
}