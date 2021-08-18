#ifndef __ENGINE_VULKAN_SWAP_CHAIN_MISC__
#define __ENGINE_VULKAN_SWAP_CHAIN_MISC__

#include "vulkan/vulkan.h"
#include "GLFW/glfw3.h"
#include <vector>
#include "GraphiquePipelineElement.hpp"
#include <map>

struct VulkanSwapChainMisc
{
    VkExtent2D str_swapChainExtent;
    VkFormat str_swapChainImageFormat;
    VkFormat str_depthFormat;
    std::vector<VkImage> str_swapChainImages;
    VkSwapchainKHR str_swapChain;
    std::vector<VkImageView> str_swapChainImageViews;
    VkRenderPass str_renderPass = VK_NULL_HANDLE;
    std::vector<VkDescriptorSetLayout> str_descriptorSetLayout;
    std::vector<GraphiquePipelineElement *> str_graphiquePipelineElement;   
    std::map<std::string,std::vector<char>> str_shaderLoader;
    VkSurfaceFormatKHR str_surfaceFormatKHR;
    VkPresentModeKHR str_presentModeKHR;
    uint32_t str_imageCount;
};

#endif //__ENGINE_VULKAN_SWAP_CHAIN_MISC__