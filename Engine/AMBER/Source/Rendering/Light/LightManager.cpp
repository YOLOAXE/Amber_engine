#include "LightManager.hpp"

namespace Ge
{
    bool LightManager::initialize(VulkanMisc *vM)
    {
        vulkanM = vM;
		if (!BufferManager::createBuffer(sizeof(UniformBufferLight), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffers, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer");
			return false;
		}
		updateDescriptor();
		vulkanM->str_VulkanDescriptor->lightCount = 0;	
		Debug::INITSUCCESS("LightManager");
        return true;
    }

    SpotLight * LightManager::createSpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutOff, float outerCutOff, std::string name)
	{
		SpotLight * light = new SpotLight(m_lights.size(), vulkanM);
		light->setPosition(position);
		light->setColors(color);
		light->setCutOff(cutOff);
		light->setOuterCutOff(outerCutOff);
		light->setName(name);
		m_lights.push_back(light);
		vulkanM->str_VulkanDescriptor->lightCount = m_lights.size();
		updateDescriptor();
		return (SpotLight *)light;
	}

	DirectionalLight * LightManager::createDirectionalLight(glm::vec3 direction, glm::vec3 color, std::string name)
	{
		DirectionalLight * light = new DirectionalLight(m_lights.size(), vulkanM);
		light->setColors(color);
		light->setName(name);		
		m_lights.push_back(light);
		vulkanM->str_VulkanDescriptor->lightCount = m_lights.size();
		updateDescriptor();
		return (DirectionalLight *)light;
	}

	PointLight * LightManager::createPointLight(glm::vec3 position, glm::vec3 color, std::string name)
	{
		PointLight * light = new PointLight(m_lights.size(), vulkanM);
		light->setPosition(position);
		light->setColors(color);	
		light->setName(name);		
		m_lights.push_back(light);
		vulkanM->str_VulkanDescriptor->lightCount = m_lights.size();
		updateDescriptor();
		return (PointLight *)light;
	}

	void LightManager::destroyLight(Lights * light)
	{
		//TODO faire la conversion si erreur
		m_lights.erase(std::remove(m_lights.begin(), m_lights.end(), light), m_lights.end());
        delete(light);
		vulkanM->str_VulkanDescriptor->lightCount = m_lights.size();
		updateDescriptor();
		majIndex();
	}

	void LightManager::release()
	{
        for (int i = 0 ; i < m_lights.size();i++)
		{
			delete(m_lights[i]);
		}
		m_lights.clear();
        vulkanM->str_VulkanDescriptor->lightCount = 0;
		BufferManager::destroyBuffer(m_vmaUniformBuffers);
		delete(m_descriptor);
		Debug::RELEASESUCCESS("light Manager");
	}

	void LightManager::updateDescriptor()
	{
		std::vector<VkDescriptorBufferInfo> bufferInfoLight{};
		VkDescriptorBufferInfo bufferIL{};
		for (int i = 0; i < m_lights.size(); i++)
		{
            bufferIL.buffer = m_lights[i]->getUniformBuffers();
			bufferIL.offset = 0;
			bufferIL.range = sizeof(UniformBufferLight);
			bufferInfoLight.push_back(bufferIL);
        }
		if(bufferInfoLight.size() == 0)
		{			
			bufferIL.buffer = m_vmaUniformBuffers.buffer;
			bufferIL.offset = 0;
			bufferIL.range = sizeof(UniformBufferLight);
			bufferInfoLight.push_back(bufferIL);
		}
				
		m_descriptor->updateCount(vulkanM, bufferInfoLight.size(),bufferInfoLight);
	}

	void LightManager::initDescriptor(VulkanMisc * vM) 
	{
		if (m_descriptor == nullptr)
		{
			m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
		}
	}

	void LightManager::majIndex()
	{
		for (int i = 0; i < m_lights.size(); i++)
		{
			m_lights[i]->setIndex(i);
		}		
	}
}