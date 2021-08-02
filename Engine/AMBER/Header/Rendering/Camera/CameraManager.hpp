#ifndef __ENGINE_CAMERA_MANAGER__
#define __ENGINE_CAMERA_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"

namespace Ge
{
    class CameraManager
    {
    public:
        bool initialized(VulkanMisc *vM);
        void release();
        static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM);
    };
}

#endif //__ENGINE_CAMERA_MANAGER__