#ifndef __ENGINE_TEXTURE_MANAGER__
#define __ENGINE_TEXTURE_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"

namespace Ge
{
    class TextureManager
    {
    public:
        bool initiliaze(VulkanMisc * vM);
        void release();
        static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM);
    };
}

#endif //__ENGINE_TEXTURE_MANAGER__