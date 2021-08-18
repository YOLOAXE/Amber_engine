#include "ShaderUniformBufferDivers.hpp"
#include "Time.hpp"

namespace Ge
{
    bool ShaderUniformBufferDivers::initialize(VulkanMisc * vM)
	{
        vulkanM = vM;		
		if (!BufferManager::createBuffer(sizeof(UniformBufferDiver), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM))
		{
			Debug::Error("Echec de la creation d'un uniform buffer Diver");
			return false;
		}
        Debug::INITSUCCESS("UniformBufferDiver");
		return true;
	}

	VkBuffer ShaderUniformBufferDivers::getUniformBuffers()
	{
		return m_vmaUniformBuffer.buffer;
	}

	void ShaderUniformBufferDivers::updateUniformBufferDiver()
	{		
		m_ubd.maxLight = vulkanM->str_VulkanDescriptor->lightCount;
		m_ubd.u_time = Time::GetTime();
		m_ubd.gamma = 1.0f;//settingM->getGamma(); //TODO ajouter le gamma	
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubd, sizeof(m_ubd));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	void ShaderUniformBufferDivers::release()
	{
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
		Debug::RELEASESUCCESS("UniformBufferDiver");
	}
}