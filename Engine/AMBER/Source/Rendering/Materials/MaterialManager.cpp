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

    Material * MaterialManager::createMaterial()
    {     
		Materials * material = new Materials(m_materials.size(), vulkanM);		
		m_materials[(Material *)material] = material;
		vulkanM->str_VulkanDescriptor->materialCount = m_materials.size();
        updateDescriptor();
		return (Material *)material;           
    }

    void MaterialManager::destroyMaterial(Material *material)
    {
        Materials * mat = m_materials[material];
        m_materials.erase(mat);
        delete(mat);
        vulkanM->str_VulkanDescriptor->materialCount = m_materials.size();
        updateDescriptor();
    }

    void MaterialManager::updateDescriptor()
    {
        std::vector<VkDescriptorBufferInfo> bufferInfoMaterial{};
		VkDescriptorBufferInfo bufferIM{};
        for (std::map<Material *, Materials *>::iterator iter = m_materials.begin(); iter != m_materials.end(); ++iter)
        {
            bufferIM.buffer = iter->second->getUniformBuffers();
			bufferIM.offset = 0;
			bufferIM.range = sizeof(UniformBufferMaterial);
			bufferInfoMaterial.push_back(bufferIM);
        }
        m_descriptor->updateCount(vulkanM,m_materials.size(),bufferInfoMaterial);
    }

    void MaterialManager::release()
    {
        for (std::map<Material *, Materials *>::iterator iter = m_materials.begin(); iter != m_materials.end(); ++iter)
		{
			delete (iter->second);
		}
		m_materials.clear();
        delete (m_descriptor);
        Debug::RELEASESUCCESS("MaterialManager");
    }

	void MaterialManager::InitDescriptor(VulkanMisc * vM)
	{
		MaterialManager::m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
	}
}