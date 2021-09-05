#ifndef __ENGINE_HUD__
#define __ENGINE_HUD__

#include "Debug.hpp"
#define GLFW_INCLUDE_NONE
#include "imgui-cmake/Header/imgui.h"
#include "imgui-cmake/Header/imgui_impl_vulkan.h"
#include "imgui-cmake/Header/imgui_impl_glfw.h"
#include "VulkanMisc.hpp"
#include <array>
#include <vector>

namespace Ge
{
	class Hud
	{
	public:
		friend class RenderingEngine;
		bool initialize(VulkanMisc* vM);
		void release();
		void recreateSwapChain();
		void render(uint32_t currentframe);
		static void check_vk_result(VkResult err);
	private:
		bool createCommandPool(VkCommandPool* commandPool, VkCommandPoolCreateFlags flags, VulkanDeviceMisc* vM);
		bool createCommandBuffers(VkCommandBuffer* commandBuffer, uint32_t commandBufferCount, VkCommandPool& commandPool, VulkanDeviceMisc* vM);
		void imGuiRender();
	private:
		friend class RenderingEngine;
		VulkanMisc* vulkanM;
		VkRenderPass m_imGuiRenderPass;
		ImGui_ImplVulkanH_Window* m_vWindow;
		VkCommandPool m_imGuiCommandPools;
		std::vector<VkFramebuffer> m_imGuiFramebuffer;
		std::vector<VkCommandBuffer> m_imGuiCommandBuffers;
		std::array<VkClearValue, 2> m_clearValues{};
		VkDescriptorPool m_imGuiDescriptorPool;
		bool m_hudActive;
		bool m_globalUI = true;
	};

}

#endif//__ENGINE_HUD__