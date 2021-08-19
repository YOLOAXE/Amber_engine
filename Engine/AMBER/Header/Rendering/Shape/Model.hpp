#ifndef __ENGINE_MODEL_SHAPE__
#define __ENGINE_MODEL_SHAPE__

#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "ModelBuffer.hpp"
#include "BufferManager.hpp"
#include "Shape.hpp"
#include "UniformBufferObject.hpp"
#include "PushConstants.hpp"
#include "GObject.hpp"

namespace Ge
{
	class Model : public Shape, public virtual GObject
	{
	public:
		Model(ModelBuffer * buffer, int indexUbo, VulkanMisc * vM);
		~Model();
		void render(VkCommandBuffer CmdBuffer, VkDescriptorSet pDescriptorSets, VkPipelineLayout pipelineLayout, VkShaderStageFlags pushConstantShaderFlags);
		VkBuffer getUniformBuffers();
		ModelBuffer * getModelBuffer();
		UniformBufferObject getUBO();
		void mapMemory() override;
		void setIndexUbo(int index);		
	private:
		VulkanMisc * vulkanM;
		ModelBuffer * m_buffer;
		VkDevice m_device;
		VmaBuffer m_vmaUniformBuffer;
		PushConstants m_index{};
		UniformBufferObject m_ubo{};
	};
}

#endif // __ENGINE_MODEL_SHAPE__
