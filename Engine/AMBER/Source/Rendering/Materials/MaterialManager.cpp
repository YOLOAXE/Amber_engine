#include "MaterialManager.hpp"

namespace Ge
{
	Descriptor * MaterialManager::m_descriptor = nullptr;
    bool MaterialManager::initialize(VulkanMisc *vM)
    {
        vulkanM = vM;
        createMaterial();
        Debug::INITSUCCESS("MaterialManager");
        return true;
    }

    Materials * MaterialManager::createMaterial()
    {     
		Materials * material = new Materials(m_materials.size(), vulkanM);		
		m_materials.push_back(material);
		vulkanM->str_VulkanDescriptor->materialCount = m_materials.size();
        updateDescriptor();
		return material;
    }

    void MaterialManager::destroyMaterial(Materials *material)
    {
		m_materials.erase(std::remove(m_materials.begin(), m_materials.end(), material), m_materials.end());
        delete(material);
        vulkanM->str_VulkanDescriptor->materialCount = m_materials.size();
        updateDescriptor();
    }

    void MaterialManager::updateDescriptor()
    {
        std::vector<VkDescriptorBufferInfo> bufferInfoMaterial{};
		VkDescriptorBufferInfo bufferIM{};
		for (int i = 0; i < m_materials.size(); i++)
		{
            bufferIM.buffer = m_materials[i]->getUniformBuffers();
			bufferIM.offset = 0;
			bufferIM.range = sizeof(UniformBufferMaterial);
			bufferInfoMaterial.push_back(bufferIM);
        }
        m_descriptor->updateCount(vulkanM,m_materials.size(),bufferInfoMaterial);
    }

    void MaterialManager::release()
    {
        for (int i = 0; i < m_materials.size();i++)
		{
			delete (m_materials[i]);
		}
		m_materials.clear();
        delete (m_descriptor);
        Debug::RELEASESUCCESS("MaterialManager");
    }

	void MaterialManager::InitDescriptor(VulkanMisc * vM)
	{
		MaterialManager::m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
	}

	Descriptor* MaterialManager::GetDescriptor()
	{
		return MaterialManager::m_descriptor;
	}
}