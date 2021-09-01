#include "TextureManager.hpp"

namespace Ge
{
	Descriptor * TextureManager::m_descriptor = nullptr;
    bool TextureManager::initiliaze(VulkanMisc *vM)
    {
        vulkanM = vM;
        stbi_uc *pixel = new stbi_uc(3);
        pixel[0] = 255;
        pixel[1] = 0;
        pixel[2] = 0;
        nullTexture = new Textures(pixel, 1, 1, m_textures.size(), vulkanM);
        m_textures[(Texture *)nullTexture] = nullTexture;
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
        for (std::map<Texture *, Textures *>::iterator iter = m_textures.begin(); iter != m_textures.end(); ++iter)
        {
            imageI.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageI.imageView = iter->second->getVkImageView();
            imageI.sampler = iter->second->getVkSampler();
            imageInfo.push_back(imageI);
        }
        m_descriptor->updateCount(vulkanM, vulkanM->str_VulkanDescriptor->textureCount, imageInfo);
    }

    void TextureManager::release()
    {
        for (std::map<Texture *, Textures *>::iterator iter = m_textures.begin(); iter != m_textures.end(); ++iter)
        {
            delete (iter->second);
        }
        m_textures.clear();
        vulkanM->str_VulkanDescriptor->textureCount = 0;
        delete (m_descriptor);
        Debug::RELEASESUCCESS("TextureManager");
    }

	void TextureManager::InitDescriptor(VulkanMisc * vM)
	{
		TextureManager::m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1);
	}

	Descriptor* TextureManager::GetDescriptor()
	{
		return TextureManager::m_descriptor;
	}

    Texture *TextureManager::createTexture(const char *path)
    {
        int tw, th, tc;
        stbi_uc *pixel = stbi_load(path, &tw, &th, &tc, STBI_rgb_alpha);
        if (!pixel)
        {
            Debug::Warn("Echec du chargement de la texture");
            return nullptr;
        }
        Textures *texture = new Textures(pixel, tw, th, m_textures.size(), vulkanM);
        m_textures[(Texture *)texture] = texture;
        stbi_image_free(pixel);
        vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
        updateDescriptor();
        return (Texture *)texture;
    }

    void TextureManager::destroyTexture(Texture *texture)
    {
        Textures *t = m_textures[texture];
        m_textures.erase(texture);
        delete (t);
        vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
        updateDescriptor();
    }
}