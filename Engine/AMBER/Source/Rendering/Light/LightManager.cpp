#include "LightManager.hpp"

namespace Ge
{
	Descriptor * LightManager::m_descriptor = nullptr;
    bool LightManager::initialize(VulkanMisc *vM)
    {
        vulkanM = vM;
		if (!BufferManager::createBuffer(sizeof(UniformBufferLight), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffers, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer");
			return false;
		}
		vulkanM->str_VulkanDescriptor->lightCount = 0;	
		updateDescriptor();	
        return true;
    }

    SpotLight * LightManager::createSpotLight(Vector3 position, Vector3 color, Vector3 direction, float cutOff, float outerCutOff, std::string name)
	{
		LSpot * light = new LSpot(m_mapLights.size(), vulkanM);
		light->setPosition(position);
		light->setColors(color);
		light->setCutOff(cutOff);
		light->setOuterCutOff(outerCutOff);
		light->setName(name);
		m_mapLights[(Light *)light] = light;    
		vulkanM->str_VulkanDescriptor->lightCount = m_mapLights.size();
		updateDescriptor();
		return (SpotLight *)light;
	}

	DirectionalLight * LightManager::createDirectionalLight(Vector3 direction, Vector3 color, std::string name)
	{
		LDirectional * light = new LDirectional(m_mapLights.size(), vulkanM);
		light->setColors(color);
		light->setName(name);		
		m_mapLights[(Light *)light] = light;        
		vulkanM->str_VulkanDescriptor->lightCount = m_mapLights.size();
		updateDescriptor();
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
		updateDescriptor();
		return (PointLight *)light;
	}

	void LightManager::destroyLight(Light * light)
	{
		Lights * li = m_mapLights[light];
        m_mapLights.erase(li);
        delete(li);
		vulkanM->str_VulkanDescriptor->lightCount = m_mapLights.size();		
		updateDescriptor();
	}

	void LightManager::release()
	{
        for (std::map<Light *, Lights *>::iterator iter = m_mapLights.begin(); iter != m_mapLights.end(); ++iter)
		{
			delete (iter->second);
		}
		m_mapLights.clear();
        vulkanM->str_VulkanDescriptor->lightCount = 0;
		BufferManager::destroyBuffer(m_vmaUniformBuffers);
		delete(m_descriptor);
		Debug::RELEASESUCCESS("light Manager");
	}

	void LightManager::updateDescriptor()
	{
		std::vector<VkDescriptorBufferInfo> bufferInfoLight{};
		VkDescriptorBufferInfo bufferIL{};
        for (std::map<Light *, Lights *>::iterator iter = m_mapLights.begin(); iter != m_mapLights.end(); ++iter)
        {
            bufferIL.buffer = iter->second->getUniformBuffers();
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
				
		m_descriptor->updateCount(vulkanM,m_mapLights.size(),bufferInfoLight);		
	}

	void LightManager::InitDescriptor(VulkanMisc * vM) 
	{
		LightManager::m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
	}

	void LightManager::majIndex()
	{
        int i = 0;
        for (std::map<Light *, Lights *>::iterator iter = m_mapLights.begin(); iter != m_mapLights.end(); ++iter)
		{
			iter->second->setIndex(i++);
		}		
	}
}