#include "DepthResources.hpp"
#include "RenderPass.hpp"
#include "ColorResources.hpp"
#include "ImageViewSwapChains.hpp"
#include "PhysicalDevices.hpp"

namespace Ge
{
	bool DepthResources::initialize(VulkanMisc * vM)
	{
		vulkanM = vM;
		VkFormat depthFormat = RenderPass::findDepthFormat(vM);
		vM->str_VulkanSwapChainMisc->str_depthFormat = depthFormat;
		VkExtent2D swapChainExtent = vM->str_VulkanSwapChainMisc->str_swapChainExtent;

		ColorResources::createImage(swapChainExtent.width, swapChainExtent.height, 1, PhysicalDevices::getMaxUsableSampleCount(vM), depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_depthImage, m_depthImageMemory, vM);
		m_depthImageView = ImageViewSwapChains::createImageView(m_depthImage, VK_IMAGE_VIEW_TYPE_2D, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1, vM);
		Debug::INITSUCCESS("DepthResources");
		vM->str_VulkanCommandeBufferMisc->str_depthImageView = m_depthImageView;
		return true;
	}

	void DepthResources::release()
	{
		vkDestroyImageView(vulkanM->str_VulkanDeviceMisc->str_device, m_depthImageView, nullptr);
		vkDestroyImage(vulkanM->str_VulkanDeviceMisc->str_device, m_depthImage, nullptr);
		vkFreeMemory(vulkanM->str_VulkanDeviceMisc->str_device, m_depthImageMemory, nullptr);
		Debug::RELEASESUCCESS("DepthResources");
	}
}