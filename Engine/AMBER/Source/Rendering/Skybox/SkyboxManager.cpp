#include "SkyboxManager.hpp"
#include "TextureManager.hpp"

namespace Ge
{
	Skybox * SkyboxManager::currentSkybox = nullptr;
	bool SkyboxManager::initialize(VulkanMisc * vM, ModelManager * mM, GraphiquePipelineManager * gPM)
	{
		vulkanM = vM;
		currentSkybox = nullptr;
		cubeMapBaseModel = mM->allocateBuffer("../Model/skybox.obj");
		m_skyboxPipeline = gPM->createPipeline("../Shader/sbFrag.spv","../Shader/sbVert.spv");
		loadSkybox(TextureManager::GetNullCubeMap());
		Debug::INITSUCCESS("SkyboxManager");
		return true;
	}

	Skybox * SkyboxManager::GetCurrentSkybox()
	{
		return currentSkybox;
	}

	void SkyboxManager::initDescriptor(VulkanMisc * vM)
	{
		if (m_descriptor == nullptr)
		{
			m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1);
		}
	}

	void SkyboxManager::updateDescriptor()
	{
		std::vector<VkDescriptorImageInfo> imageInfo{};
		VkDescriptorImageInfo imageI{};
		for (int i = 0; i < 1; i++)
		{
			imageI.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageI.imageView = currentSkybox->getTextureCubeMap()->getVkImageView();
			imageI.sampler = currentSkybox->getTextureCubeMap()->getVkSampler();
			imageInfo.push_back(imageI);
		}
		m_descriptor->updateCount(vulkanM, 1, imageInfo);
	}

	void SkyboxManager::loadSkybox(TextureCubeMap * tCM)
	{		
		if (currentSkybox != nullptr)
		{
			delete(currentSkybox);
		}
		currentSkybox = new Skybox(tCM, cubeMapBaseModel, m_skyboxPipeline->getIndex());
		updateDescriptor();
	}

	void SkyboxManager::release()
	{
		if (currentSkybox != nullptr)
		{
			delete(currentSkybox);
		}
		delete (m_descriptor);
		Debug::RELEASESUCCESS("SkyboxManager");
	}
}