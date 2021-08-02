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
        VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 0;
		samplerLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->TextureCount == 0 ? 1 : vM->str_VulkanDescriptor->TextureCount);
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;
    }
}