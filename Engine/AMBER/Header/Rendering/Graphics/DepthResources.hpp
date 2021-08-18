#ifndef __ENGINE_DEPTH_RESOURCES__
#define __ENGINE_DEPTH_RESOURCES__

#include "VulkanMisc.hpp"
#include "Debug.hpp"

namespace Ge
{
	class DepthResources
	{
	private:
		friend class RenderingEngine;
		bool initialize(VulkanMisc * vM);
		void release();
	private:
		VulkanMisc * vulkanM;
		VkImage m_depthImage;
		VkDeviceMemory m_depthImageMemory;
		VkImageView m_depthImageView;
	};
}

#endif//__ENGINE_DEPTH_RESOURCES__