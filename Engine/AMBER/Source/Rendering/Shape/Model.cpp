#include "Model.hpp"

namespace Ge
{
	Model::Model(ModelBuffer * buffer, int indexubo, VulkanMisc * vM) : GObject()
	{
		vulkanM = vM;
		m_buffer = buffer;
		m_device = vM->str_VulkanDeviceMisc->str_device;

		if (!BufferManager::createBuffer(sizeof(UniformBufferObject), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc)) 
		{
			Debug::Error("Echec de la creation d'un uniform buffer object");
		}
		m_index.ubo = indexubo;
		m_index.material = 0;
	}

	Model::~Model()
	{
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
	}

	void Model::render(VkCommandBuffer CmdBuffer, std::vector<VkDescriptorSet> descriptorSets, VkPipelineLayout pipelineLayout, VkShaderStageFlags pushConstantShaderFlags)
	{
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(CmdBuffer, 0, 1, m_buffer->getVertexBuffer(), offsets);

		vkCmdBindIndexBuffer(CmdBuffer, m_buffer->getIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);

		vkCmdBindDescriptorSets(CmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, static_cast<uint32_t>(descriptorSets.size()), descriptorSets.data(), 0, nullptr);

		vkCmdPushConstants(
			CmdBuffer,
			pipelineLayout,
			pushConstantShaderFlags,
			0,
			sizeof(PushConstants),
			&m_index);

		vkCmdDrawIndexed(CmdBuffer, m_buffer->getIndiceSize(), 1, 0, 0, 0);
	}

	void Model::mapMemory()
	{
		m_ubo.model = m_transform.translateMatrix * m_transform.rotationMatrix;
		m_ubo.model = glm::scale(m_ubo.model, m_transform.scale);

		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubo, sizeof(m_ubo));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	void Model::setMaterial(Material * m)
	{
		m_material = m;
		m_index.material = m_material->getIndex();
	}

	Material * Model::getMaterial()
	{
		return m_material;
	}

	VkBuffer Model::getUniformBuffers()
	{
		return m_vmaUniformBuffer.buffer;
	}

	ModelBuffer * Model::getModelBuffer()
	{
		return m_buffer;
	}

	UniformBufferObject Model::getUBO()
	{
		return m_ubo;
	}

	void Model::setIndexUbo(int index)
	{
		m_index.ubo = index;
	}

}
