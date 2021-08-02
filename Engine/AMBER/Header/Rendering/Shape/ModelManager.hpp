#ifndef __ENGINE_MODEL_MANAGER___
#define __ENGINE_MODEL_MANAGER___

#include "VulkanMisc.hpp"
#include "Debug.hpp"

namespace Ge
{
    class ModelManager
    {
        public:
            bool initiliaze(VulkanMisc * vM);
            void release();
            static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM);

    };
}

#endif //__ENGINE_MODEL_MANAGER___