#ifndef __ENGINE_SWAP_CHAIN__
#define __ENGINE_SWAP_CHAIN__

#include "Debug.hpp"
#include <algorithm>
#include "SwapChainSupportDetails.hpp"
#include "QueueFamilyIndices.hpp"
#include "ImageViewSwapChains.hpp"
#include "RenderPass.hpp"
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
		bool initializeLayout();
		void releaseLayout();
	private:
		VkExtent2D m_swapChainExtent;
		VkFormat m_swapChainImageFormat;
		std::vector<VkImage> m_swapChainImages;
		std::vector<ImageViewSwapChains *> m_swapChainImagesView;
		DescriptorLayoutManager m_descriptorLayoutManager;
		RenderPass m_renderPass;
		VkSwapchainKHR m_swapChain;
		uint32_t m_imageCount;
		VulkanMisc * vulkanM;
	};
}

#endif //__ENGINE_SWAP_CHAIN__