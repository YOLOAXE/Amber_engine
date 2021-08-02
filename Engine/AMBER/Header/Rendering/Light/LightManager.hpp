#ifndef __ENGINE_LIGHT_MANAGER__
#define __ENGINE_LIGHT_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"

namespace Ge
{
    class LightManager
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();
        static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM);
    };
}

#endif //__ENGINE_LIGHT_MANAGER__