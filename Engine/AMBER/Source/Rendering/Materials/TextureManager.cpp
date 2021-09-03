#include "TextureManager.hpp"

namespace Ge
{
    bool TextureManager::initiliaze(VulkanMisc *vM)
    {
        vulkanM = vM;
        stbi_uc *pixel = new stbi_uc[3];
        pixel[0] = 255;
        pixel[1] = 0;
        pixel[2] = 0;
        nullTexture = new Textures(pixel, 1, 1, m_textures.size(), vulkanM);
        m_textures.push_back(nullTexture);
        vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
        delete (pixel);  
        updateDescriptor();      
        Debug::INITSUCCESS("TextureManager");
        return true;
    }

    void TextureManager::updateDescriptor()
    {
        std::vector<VkDescriptorImageInfo> imageInfo{};        
        VkDescriptorImageInfo imageI{};
        for (int i = 0; i < m_textures.size();i++)
        {
            imageI.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageI.imageView = m_textures[i]->getVkImageView();
            imageI.sampler = m_textures[i]->getVkSampler();
            imageInfo.push_back(imageI);
        }
        m_descriptor->updateCount(vulkanM, vulkanM->str_VulkanDescriptor->textureCount, imageInfo);
    }

    void TextureManager::release()
    {
		for (int i = 0; i < m_textures.size(); i++)
		{
            delete (m_textures[i]);
        }
        m_textures.clear();
        vulkanM->str_VulkanDescriptor->textureCount = 0;
        delete (m_descriptor);
        Debug::RELEASESUCCESS("TextureManager");
    }

	void TextureManager::initDescriptor(VulkanMisc * vM)
	{
		if (m_descriptor == nullptr)
		{
			m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1);
		}
	}

    Textures *TextureManager::createTexture(const char *path)
    {
        int tw, th, tc;
        stbi_uc *pixel = stbi_load(path, &tw, &th, &tc, STBI_rgb_alpha);
        if (!pixel)
        {
            Debug::Warn("Echec du chargement de la texture");
            return nullptr;
        }
        Textures *texture = new Textures(pixel, tw, th, m_textures.size(), vulkanM);
        m_textures.push_back(texture);
        stbi_image_free(pixel);
        vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
        updateDescriptor();
        return texture;
    }

    void TextureManager::destroyTexture(Textures *texture)
    {
		m_textures.erase(std::remove(m_textures.begin(), m_textures.end(), texture), m_textures.end());
        delete (texture);
        vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
        updateDescriptor();
    }
}