#ifndef __ENGINE_VULKAN_DESCRIPTOR__
#define __ENGINE_VULKAN_DESCRIPTOR__

#include "vulkan/vulkan.h"
#include <vector>

struct VulkanDescriptor
{
    VkDescriptorPool str_descriptorPool = VK_NULL_HANDLE;
	VkDescriptorPool str_imGUIdescriptorPool = VK_NULL_HANDLE;
	std::vector<VkDescriptorSet> str_descriptorSets;
    int modelCount = 0;
    int TextureCount = 0;
    int materialCount = 0;
    int lightCount = 0;
};

#endif //__ENGINE_VULKAN_DESCRIPTOR__