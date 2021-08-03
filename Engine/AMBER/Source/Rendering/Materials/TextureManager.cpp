#include "TextureManager.hpp"

namespace Ge
{
    bool TextureManager::initiliaze(VulkanMisc *vM)
    {
        return true;
    }

    void TextureManager::release()
    {
    }

    VkDescriptorSetLayout TextureManager::createVkDescriptorSetLayout(VulkanMisc *vM)
    {
        VkDescriptorSetLayout m_descriptorSetLayout;
        VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 0;
		samplerLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->TextureCount == 0 ? 1 : vM->str_VulkanDescriptor->TextureCount);
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;
        
        VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = 1;
		layoutInfo.pBindings = &samplerLayoutBinding;

		if (vkCreateDescriptorSetLayout(vM->str_VulkanDeviceMisc->str_device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation du descriptor set layout");		
		}

        return m_descriptorSetLayout;
    }
}