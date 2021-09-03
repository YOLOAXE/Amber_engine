#include "ShaderUniformBufferDivers.hpp"
#include "Time.hpp"

namespace Ge
{
    bool ShaderUniformBufferDivers::initialize(VulkanMisc * vM, SettingManager * sM)
	{
        vulkanM = vM;		
		settingM = sM;
		if (!BufferManager::createBuffer(sizeof(UniformBufferDiver), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer Diver");
			return false;
		}
		updateDescriptor();
        Debug::INITSUCCESS("UniformBufferDiver");
		return true;
	}

	void ShaderUniformBufferDivers::updateUniformBufferDiver()
	{		
		m_ubd.maxLight = vulkanM->str_VulkanDescriptor->lightCount;
		m_ubd.u_time = Time::GetTime();
		m_ubd.gamma = settingM->getGamma();
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubd, sizeof(m_ubd));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	void ShaderUniformBufferDivers::initDescriptor(VulkanMisc * vM)
	{
		if (m_descriptor == nullptr)
		{
			m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
		}
	}

	void ShaderUniformBufferDivers::updateDescriptor()
	{ 
		std::vector<VkDescriptorBufferInfo> bufferInfo;
		VkDescriptorBufferInfo bufferI{};
		bufferI.buffer = m_vmaUniformBuffer.buffer;
		bufferI.offset = 0;
		bufferI.range = sizeof(UniformBufferDiver);
		bufferInfo.push_back(bufferI);
		m_descriptor->updateCount(vulkanM, 1, bufferInfo);
	}

	void ShaderUniformBufferDivers::release()
	{
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
		delete(m_descriptor);
		Debug::RELEASESUCCESS("UniformBufferDiver");
	}
}