#ifndef __ENGINE_MATERIAL_MANAGER__
#define __ENGINE_MATERIAL_MANAGER__

#include "Debug.hpp"
#include "VulkanMisc.hpp"

namespace Ge
{
    class MaterialManager
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();
        static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM);

    };
}

#endif //__ENGINE_MATERIAL_MANAGER__