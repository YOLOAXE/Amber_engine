#ifndef __ENGINE_MATERIAL_MANAGER__
#define __ENGINE_MATERIAL_MANAGER__

#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "Descriptor.hpp"

namespace Ge
{
    class MaterialManager
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();
        static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM);
        static VkDescriptorPool createVkDescriptorPool(VulkanMisc *vM);

    public:
        static Descriptor *m_descriptor;
    };
}

#endif //__ENGINE_MATERIAL_MANAGER__