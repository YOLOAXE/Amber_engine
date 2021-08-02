#include "DescriptorLayoutManager.hpp"
#include "CameraManager.hpp"
#include "ModelManager.hpp"

namespace Ge
{

    bool DescriptorLayoutManager::initialize(VulkanMisc *vM)
    {
		vulkanM = vM;
        /*
		VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 1;
		samplerLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->TextureCount == 0 ? 1 : vM->str_VulkanDescriptor->TextureCount);
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding ubmLayoutBinding{};
		ubmLayoutBinding.binding = 2;
		ubmLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->materialCount == 0 ? 1 : vM->str_VulkanDescriptor->materialCount);
		ubmLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ubmLayoutBinding.pImmutableSamplers = nullptr;
		ubmLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding ublLayoutBinding{};
		ublLayoutBinding.binding = 3;
		ublLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->lightCount == 0 ? 1 : vM->str_VulkanDescriptor->lightCount);
		ublLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ublLayoutBinding.pImmutableSamplers = nullptr;
		ublLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutBinding ubdLayoutBinding{};
		ubdLayoutBinding.binding = 4;
		ubdLayoutBinding.descriptorCount = 1;
		ubdLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		ubdLayoutBinding.pImmutableSamplers = nullptr;
		ubdLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

		std::array<VkDescriptorSetLayoutBinding, 5> bindings = { uboLayoutBinding, samplerLayoutBinding, ubmLayoutBinding, ublLayoutBinding, ubdLayoutBinding };

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(vM->str_VulkanDeviceMisc->str_device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation du descriptor set layout");
			return false;
		}*/
		vM->str_VulkanSwapChainMisc->str_descriptorSetLayout.push_back(ModelManager::createVkDescriptorSetLayout(vM));
		vM->str_VulkanSwapChainMisc->str_descriptorSetLayout.push_back(CameraManager::createVkDescriptorSetLayout(vM));
        Debug::INITSUCCESS("DescriptorLayoutManager");
        return true;
    }

    void DescriptorLayoutManager::release()
    {
		for(int i = 0; i < vulkanM->str_VulkanSwapChainMisc->str_descriptorSetLayout.size(); i++)
		{
        	vkDestroyDescriptorSetLayout(vulkanM->str_VulkanDeviceMisc->str_device, vulkanM->str_VulkanSwapChainMisc->str_descriptorSetLayout[0], nullptr);
		}
    }

}