#ifndef __ENGINE_SWAP_CHAIN__
#define __ENGINE_SWAP_CHAIN__

#include "Debug.hpp"
#include <algorithm>
#include "SwapChainSupportDetails.hpp"
#include "QueueFamilyIndices.hpp"
#include "ImageViewSwapChains.hpp"
#include "RenderPass.hpp"
#include "GraphiquePipelineManager.hpp"
#include "DescriptorLayoutManager.hpp"

namespace Ge
{
	class SwapChain
	{
	public:
		static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VulkanDeviceMisc * vDM);// verifier qu'elle est compatible la surface de fen�tre(Window Surface)
	private:
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, VulkanDeviceMisc * vDM);
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	private:
		friend class RenderingEngine;
		bool initialize(VulkanMisc * vM);
		void release();
		bool initPipeline();
		void releasePipeline();
	private:
		VkExtent2D m_swapChainExtent;
		VkFormat m_swapChainImageFormat;
		std::vector<VkImage> m_swapChainImages;
		std::vector<ImageViewSwapChains *> m_swapChainImagesView;
		RenderPass m_renderPass;
		DescriptorLayoutManager m_descriptorLayoutManager;
		GraphiquePipelineManager m_graphiquePipelineManager;
		VkSwapchainKHR m_swapChain;
		uint32_t m_imageCount;
		VulkanMisc * vulkanM;
	};
}

#endif //__ENGINE_SWAP_CHAIN__