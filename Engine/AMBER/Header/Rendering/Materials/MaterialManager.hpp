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
        Materials *createMaterial();
        void destroyMaterial(Materials *material);
		static void InitDescriptor(VulkanMisc * vM);
		static Descriptor* GetDescriptor();
    private:
        void updateDescriptor();

    private:
        std::vector<Materials *> m_materials;
        VulkanMisc *vulkanM;
        static Descriptor *m_descriptor;
    };
}

#endif //__ENGINE_MATERIAL_MANAGER__