#include "LightManager.hpp"

namespace Ge
{
    bool LightManager::initialize(VulkanMisc *vM)
    {
        return true;
    }

    void release()
    {
    }

    VkDescriptorSetLayout LightManager::createVkDescriptorSetLayout(VulkanMisc *vM)
    {
        VkDescriptorSetLayout m_descriptorSetLayout;
        VkDescriptorSetLayoutBinding ublLayoutBinding{};
        ublLayoutBinding.binding = 1;
        ublLayoutBinding.descriptorCount = (vM->str_VulkanDescriptor->lightCount == 0 ? 1 : vM->str_VulkanDescriptor->lightCount);
        ublLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        ublLayoutBinding.pImmutableSamplers = nullptr;
        ublLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT | VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &ublLayoutBinding;

        if (vkCreateDescriptorSetLayout(vM->str_VulkanDeviceMisc->str_device, &layoutInfo, nullptr, &m_descriptorSetLayout) != VK_SUCCESS)
        {
            Debug::Error("Echec de la creation du descriptor set layout");
        }
        return m_descriptorSetLayout;
    }
}