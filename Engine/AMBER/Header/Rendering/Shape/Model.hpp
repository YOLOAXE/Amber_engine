#ifndef __ENGINE_MODEL_SHAPE__
#define __ENGINE_MODEL_SHAPE__

#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "ShapeBuffer.hpp"
#include "BufferManager.hpp"
#include "UniformBufferObject.hpp"
#include "PushConstants.hpp"
#include "Materials.hpp"
#include "GObject.hpp"

namespace Ge
{
	class Model : public GObject
	{
	public:
		Model(ShapeBuffer * buffer, int indexUbo, VulkanMisc * vM);
		~Model();
		void render(VkCommandBuffer CmdBuffer, std::vector<VkDescriptorSet> descriptorSets, VkPipelineLayout pipelineLayout, VkShaderStageFlags pushConstantShaderFlags);
		VkBuffer getUniformBuffers();
		ShapeBuffer * getShapeBuffer();
		UniformBufferObject getUBO();
		void setMaterial(Materials * m);
		Materials * getMaterial();
		void mapMemory() override;
		void setIndexUbo(int index);		
	private:
		VulkanMisc * vulkanM;
		ShapeBuffer * m_buffer;
		Materials * m_material;
		VkDevice m_device;
		VmaBuffer m_vmaUniformBuffer;
		PushConstants m_index{};
		UniformBufferObject m_ubo{};
	};
}

#endif // __ENGINE_MODEL_SHAPE__
