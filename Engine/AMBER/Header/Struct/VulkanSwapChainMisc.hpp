#ifndef __ENGINE_VULKAN_SWAP_CHAIN_MISC__
#define __ENGINE_VULKAN_SWAP_CHAIN_MISC__

#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include <vector>

struct VulkanSwapChainMisc
{
    VkExtent2D str_swapChainExtent;
    VkFormat str_swapChainImageFormat;
    VkFormat str_depthFormat;
    std::vector<VkImage> str_swapChainImages;
    VkSwapchainKHR str_swapChain;
    std::vector<VkImageView> str_swapChainImageViews;
    VkRenderPass str_renderPass = VK_NULL_HANDLE;
    VkDescriptorSetLayout str_descriptorSetLayout;
    VkPipeline str_graphicsPipeline = VK_NULL_HANDLE;
    VkPipeline str_graphicsPipelineSkybox = VK_NULL_HANDLE;
    VkPipelineCache str_graphicsPipelineCache = VK_NULL_HANDLE;
    VkPipelineLayout str_pipelineLayout = VK_NULL_HANDLE;
    uint32_t str_imageCount;
    VkSurfaceFormatKHR str_surfaceFormatKHR;
    VkPresentModeKHR str_presentModeKHR;
};

#endif //__ENGINE_VULKAN_SWAP_CHAIN_MISC__