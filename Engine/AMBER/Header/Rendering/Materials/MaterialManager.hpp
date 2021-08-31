#ifndef __ENGINE_MATERIAL_MANAGER__
#define __ENGINE_MATERIAL_MANAGER__

#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "Descriptor.hpp"
#include "Materials.hpp"
#include <map>

namespace Ge
{
    class MaterialManager
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();
        Material *createMaterial();
        void destroyMaterial(Material *material);
        static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM);
        static VkDescriptorPool createVkDescriptorPool(VulkanMisc *vM);

    private:
        void updateDescriptor();

    private:
        std::map<Material *, Materials *> m_materials;
        VulkanMisc *vulkanM;

    public:
        static Descriptor *m_descriptor;
    };
}

#endif //__ENGINE_MATERIAL_MANAGER__