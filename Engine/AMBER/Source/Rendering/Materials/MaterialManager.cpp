#include "MaterialManager.hpp"

namespace Ge
{
    bool MaterialManager::initialize(VulkanMisc *vM)
    {
        return true;
    }

    void MaterialManager::release()
    {
    }

    VkDescriptorSetLayout MaterialManager::createVkDescriptorSetLayout(VulkanMisc *vM)
    {
        VkDescriptorSetLayout m_descriptorSetLayout;
        VkDescriptorSetLayoutBinding ubmLayoutBinding{};
        ubmLayoutBinding.binding = 0;
        ubmLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->materialCount == 0 ? 1 : vM->str_VulkanDescriptor->materialCount);
        ubmLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        ubmLayoutBinding.pImmutableSamplers = nullptr;
        ubmLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &ubmLayoutBinding;

        if (vkCreateDescriptorSetLayout(vM->str_VulkanDeviceMisc->str_device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS)
        {
            Debug::Error("Echec de la creation du descriptor set layout");
        }
        return m_descriptorSetLayout;
    }
}