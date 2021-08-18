#include "DescriptorLayoutManager.hpp"
#include "CameraManager.hpp"
#include "ModelManager.hpp"
#include "TextureManager.hpp"
#include "MaterialManager.hpp"
#include "LightManager.hpp"
#include "ShaderUniformBufferDivers.hpp"

namespace Ge
{
	bool DescriptorLayoutManager::initialize(VulkanMisc *vM)
	{		
		CameraManager::m_descriptor = new Descriptor(vM,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,1);
		TextureManager::m_descriptor = new Descriptor(vM,VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,1);
		ModelManager::m_descriptor = new Descriptor(vM,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,1);
		MaterialManager::m_descriptor = new Descriptor(vM,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,1);
		LightManager::m_descriptor = new Descriptor(vM,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,1);
		ShaderUniformBufferDivers::m_descriptor = new Descriptor(vM,VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,1);
		
		Debug::INITSUCCESS("DescriptorLayoutManager");
		return true;
	}
}