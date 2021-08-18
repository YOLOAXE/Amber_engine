#include "TextureManager.hpp"

namespace Ge
{
    bool TextureManager::initiliaze(VulkanMisc *vM)
    {
        vulkanM = vM;
        stbi_uc * pixel = new stbi_uc(3);
        pixel[0] = 0;
        pixel[1] = 0;
        pixel[2] = 255;
        nullTexture = new Textures(pixel, 1, 1, m_textures.size(), vulkanM);
        m_textures[(Texture *)nullTexture] = nullTexture;
        vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
        delete(pixel);
        Debug::INITSUCCESS("TextureManager");
        return true;
    }

    void TextureManager::release()
    {
        for(std::map<Texture *,Textures *>::iterator iter = m_textures.begin(); iter != m_textures.end(); ++iter)
        {            
            delete(iter->second);                          
        }
        m_textures.clear();
        vulkanM->str_VulkanDescriptor->textureCount = 0;
        delete(m_descriptor);
        Debug::RELEASESUCCESS("TextureManager");
    }

    Texture *TextureManager::CreateTexture(const char *path)
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
        return (Texture *)texture;
    }

    void TextureManager::DestroyTexture(Texture *texture)
    {
        Textures *t = m_textures[texture];
        m_textures.erase(texture);
        delete (t);
        vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
    }
}