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
		CameraManager::InitDescriptor(vM);
		TextureManager::InitDescriptor(vM);
		ModelManager::InitDescriptor(vM);
		MaterialManager::InitDescriptor(vM);
		LightManager::InitDescriptor(vM);
		ShaderUniformBufferDivers::InitDescriptor(vM);
		
		Debug::INITSUCCESS("DescriptorLayoutManager");
		return true;
	}
}