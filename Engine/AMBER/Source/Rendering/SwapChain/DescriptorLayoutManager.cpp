#include "DescriptorLayoutManager.hpp"
#include "CameraManager.hpp"
#include "ModelManager.hpp"
#include "TextureManager.hpp"
#include "MaterialManager.hpp"
#include "LightManager.hpp"

namespace Ge
{
	bool DescriptorLayoutManager::initialize(VulkanMisc *vM)
	{
		vulkanM = vM;
		vM->str_VulkanSwapChainMisc->str_descriptorSetLayout.push_back(CameraManager::createVkDescriptorSetLayout(vM));		
		vM->str_VulkanSwapChainMisc->str_descriptorSetLayout.push_back(TextureManager::createVkDescriptorSetLayout(vM));	
		vM->str_VulkanSwapChainMisc->str_descriptorSetLayout.push_back(ModelManager::createVkDescriptorSetLayout(vM));	
		vM->str_VulkanSwapChainMisc->str_descriptorSetLayout.push_back(MaterialManager::createVkDescriptorSetLayout(vM));				
		vM->str_VulkanSwapChainMisc->str_descriptorSetLayout.push_back(LightManager::createVkDescriptorSetLayout(vM));
		Debug::INITSUCCESS("DescriptorLayoutManager");
		return true;
	}

	void DescriptorLayoutManager::release()
	{
		for (int i = 0; i < vulkanM->str_VulkanSwapChainMisc->str_descriptorSetLayout.size(); i++)
		{
			vkDestroyDescriptorSetLayout(vulkanM->str_VulkanDeviceMisc->str_device, vulkanM->str_VulkanSwapChainMisc->str_descriptorSetLayout[i], nullptr);
		}
	}

}