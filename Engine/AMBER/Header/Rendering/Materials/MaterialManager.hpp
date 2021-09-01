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
		static void InitDescriptor(VulkanMisc * vM);
		static Descriptor* GetDescriptor();
    private:
        void updateDescriptor();

    private:
        std::map<Material *, Materials *> m_materials;
        VulkanMisc *vulkanM;

    private:
		friend class Materials;
        static Descriptor *m_descriptor;
    };
}

#endif //__ENGINE_MATERIAL_MANAGER__