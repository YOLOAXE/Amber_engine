#include "ShaderUniformBufferDivers.hpp"
#include "Time.hpp"

namespace Ge
{
	Descriptor * ShaderUniformBufferDivers::m_descriptor = nullptr;
    bool ShaderUniformBufferDivers::initialize(VulkanMisc * vM)
	{
        vulkanM = vM;		
		if (!BufferManager::createBuffer(sizeof(UniformBufferDiver), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer Diver");
			return false;
		}
		std::vector<VkDescriptorBufferInfo> bufferInfo;
        VkDescriptorBufferInfo bufferI{};
        bufferI.buffer = m_vmaUniformBuffer.buffer;
        bufferI.offset = 0;
        bufferI.range = sizeof(UniformBufferDiver);
        bufferInfo.push_back(bufferI);        
        m_descriptor->updateCount(vM,1,bufferInfo);  		
        Debug::INITSUCCESS("UniformBufferDiver");
		return true;
	}

	void ShaderUniformBufferDivers::updateUniformBufferDiver()//TODO update que si il y a un des elements qui change
	{		
		m_ubd.maxLight = vulkanM->str_VulkanDescriptor->lightCount;
		m_ubd.u_time = Time::GetTime();
		m_ubd.gamma = 1.0f;//settingM->getGamma(); //TODO ajouter le gamma	
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubd, sizeof(m_ubd));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	void ShaderUniformBufferDivers::InitDescriptor(VulkanMisc * vM)
	{
		ShaderUniformBufferDivers::m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
	}

	void ShaderUniformBufferDivers::release()
	{
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
		delete(m_descriptor);
		Debug::RELEASESUCCESS("UniformBufferDiver");
	}
}