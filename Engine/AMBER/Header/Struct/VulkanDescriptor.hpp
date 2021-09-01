#ifndef __ENGINE_VULKAN_DESCRIPTOR__
#define __ENGINE_VULKAN_DESCRIPTOR__

#include "vulkan/vulkan.h"
#include <vector>

struct VulkanDescriptor
{    
    int modelCount = 0;
    int textureCount = 0;
    int materialCount = 0;
    int lightCount = 0;
};

#endif //__ENGINE_VULKAN_DESCRIPTOR__