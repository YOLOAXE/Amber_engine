#ifndef __ENGINE_VULKAN_MISC____
#define __ENGINE_VULKAN_MISC____

#include "VulkanDeviceMisc.hpp"
#include "VulkanSwapChainMisc.hpp"
#include "VulkanCommandeBufferMisc.hpp"

struct VulkanMisc
{
    VulkanDeviceMisc *str_VulkanDeviceMisc;
    VulkanSwapChainMisc *str_VulkanSwapChainMisc;
    VulkanCommandeBufferMisc *str_VulkanCommandeBufferMisc;
};

#endif //__ENGINE_VULKAN_MISC____