#include "LightManager.hpp"

namespace Ge
{
    bool LightManager::initialize(VulkanMisc *vM)
    {
        vulkanM = vM;
        return true;
    }

    SpotLight * LightManager::createSpotLight(Vector3 position, Vector3 color, Vector3 direction, float cutOff, float outerCutOff, std::string name)
	{
		LSpot * light = new LSpot(m_mapLights.size(), vulkanM);
		light->setPosition(position);
		light->setColors(color);
		light->setDirection(direction);
		light->setCutOff(cutOff);
		light->setOuterCutOff(outerCutOff);
		light->setName(name);
		m_mapLights[(Light *)light] = light;    
		vulkanM->str_VulkanDescriptor->lightCount = m_mapLights.size();
		return (SpotLight *)light;
	}

	DirectionalLight * LightManager::createDirectionalLight(Vector3 direction, Vector3 color, std::string name)
	{
		LDirectional * light = new LDirectional(m_mapLights.size(), vulkanM);
		light->setColors(color);
		light->setDirection(direction);
		light->setName(name);		
		m_mapLights[(Light *)light] = light;        
		vulkanM->str_VulkanDescriptor->lightCount = m_mapLights.size();
		return (DirectionalLight *)light;
	}

	PointLight * LightManager::createPointLight(Vector3 position, Vector3 color, std::string name)
	{
		LPoint * light = new LPoint(m_mapLights.size(), vulkanM);
		light->setPosition(position);
		light->setColors(color);	
		light->setName(name);		
		m_mapLights[(Light *)light] = light;
		vulkanM->str_VulkanDescriptor->lightCount = m_mapLights.size();
		return (PointLight *)light;
	}

	void LightManager::destroyLight(Light * light)
	{
		Lights * li = m_mapLights[light];
        m_mapLights.erase(li);
        delete(li);
		vulkanM->str_VulkanDescriptor->lightCount = m_mapLights.size();		
	}

	void LightManager::updateUniformBufferLight()
	{
		for (std::map<Light *, Lights *>::iterator iter = m_mapLights.begin(); iter != m_mapLights.end(); ++iter)
		{
			iter->second->updateUniformBufferLight();
		}	
	}

	void LightManager::release()
	{
        for (std::map<Light *, Lights *>::iterator iter = m_mapLights.begin(); iter != m_mapLights.end(); ++iter)
		{
			delete (iter->second);
		}
		m_mapLights.clear();
        vulkanM->str_VulkanDescriptor->lightCount = 0;
		delete(m_descriptor);
		Debug::RELEASESUCCESS("light Manager");
	}

	void LightManager::majIndex()
	{
        int i = 0;
        for (std::map<Light *, Lights *>::iterator iter = m_mapLights.begin(); iter != m_mapLights.end(); ++iter)
		{
			iter->second->setIndex(i++);
		}		
	}

    VkDescriptorPool LightManager::createVkDescriptorPool(VulkanMisc *vM)
    {
        VkDescriptorPool m_descriptorPool;
        VkDescriptorPoolSize poolSizes{};				
		poolSizes.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes.descriptorCount = static_cast<uint32_t>(vM->str_VulkanSwapChainMisc->str_swapChainImages.size() * vM->str_VulkanDescriptor->lightCount);
		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSizes;
		poolInfo.maxSets = static_cast<uint32_t>(vM->str_VulkanSwapChainMisc->str_swapChainImages.size());

		if (vkCreateDescriptorPool(vM->str_VulkanDeviceMisc->str_device, &poolInfo, nullptr, &m_descriptorPool) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un descriptor pool");		
		}
		s_vkDescriptorPool = &m_descriptorPool;
		vM->str_VulkanDescriptor->str_descriptorPool.push_back(m_descriptorPool);
        return m_descriptorPool;
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
        LightManager::s_vkDescriptorSetLayout = &m_descriptorSetLayout;
        return m_descriptorSetLayout;
    }
}