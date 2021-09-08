#include "TextureManager.hpp"
namespace fs = std::filesystem;

namespace Ge
{
	TextureCubeMap * TextureManager::s_nullTextureCubeMap = nullptr;
	bool TextureManager::initialize(VulkanMisc *vM)
	{
		vulkanM = vM;
		stbi_uc *pixel = new stbi_uc[24];
		for (int i = 0; i < 24; i++)
		{
			pixel[i] = 255;			
		}
		nullTexture = new Textures(pixel, 4, 3, m_textures.size(), vulkanM);
		std::vector<unsigned char *> pixelTab = convertCubMap(pixel, 4, 3);
		s_nullTextureCubeMap = new TextureCubeMap(pixelTab, 4, 3, m_textures.size(), vulkanM);
		m_textures.push_back(nullTexture);
		m_texturesCube.push_back(s_nullTextureCubeMap);
		vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
		vulkanM->str_VulkanDescriptor->textureCubeCount = m_texturesCube.size();
		delete (pixel);
		for (int i = 0; i < pixelTab.size(); i++)
		{
			delete(pixelTab[i]);
		}
		updateDescriptor();
		Debug::INITSUCCESS("TextureManager");
		return true;
	}

	TextureCubeMap * TextureManager::GetNullCubeMap()
	{
		return TextureManager::s_nullTextureCubeMap;
	}


	void TextureManager::updateDescriptor()
	{
		std::vector<VkDescriptorImageInfo> imageInfo{};
		VkDescriptorImageInfo imageI{};
		for (int i = 0; i < m_textures.size(); i++)
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
		for (int i = 0; i < m_texturesCube.size(); i++)
		{
			delete (m_texturesCube[i]);
		}
		m_texturesCube.clear();
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
		if (fs::exists(path))
		{
			int tw, th, tc;
			unsigned char * pixel = stbi_load(path, &tw, &th, &tc, STBI_rgb_alpha);
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
		Debug::Warn("Le fichier n'existe pas");
		return nullptr;
	}

	void TextureManager::destroyTextureCubeMap(TextureCubeMap * texture)
	{
		m_texturesCube.erase(std::remove(m_texturesCube.begin(), m_texturesCube.end(), texture), m_texturesCube.end());
		delete (texture);
		vulkanM->str_VulkanDescriptor->textureCount = m_texturesCube.size();
		updateDescriptor();
	}

	std::vector<unsigned char *> TextureManager::convertCubMap(unsigned char * pixel, int tw, int th)
	{
		int twCubeMap = tw;
		int thCubeMap = (th * 4) / 3;
		std::vector<unsigned char *> pixelTab;
		std::vector<unsigned char *> pixelTabCubeMap;
		int indiceCubeMap[6] = { 4 , 5 , 6 , 7 , 1, 9 };
		for (int i = 0; i < 12; i++)
		{
			pixelTab.push_back(new stbi_uc[twCubeMap * thCubeMap]);
		}
		for (int y = 0; y < th * 4; y++)
		{
			for (int x = 0; x < tw * 4; x++)
			{
				pixelTab[(x / twCubeMap) + (y / thCubeMap) * 4][(x%twCubeMap) + ((y%thCubeMap)*twCubeMap)] = pixel[x + (y*th * 4)];
			}
		}
		for (int i = 0; i < 6; i++)
		{
			pixelTabCubeMap.push_back(pixelTab[indiceCubeMap[i]]);
		}
		return pixelTabCubeMap;
	}

	TextureCubeMap *TextureManager::createTextureCubeMap(const char *path)
	{
		if (fs::exists(path))
		{
			int tw, th, tc;
			unsigned char * pixel = stbi_load(path, &tw, &th, &tc, STBI_rgb_alpha);
			if (!pixel)
			{
				Debug::Warn("Echec du chargement de la texture");
				return nullptr;
			}
			std::vector<unsigned char *> pixelTab = convertCubMap(pixel, tw, th);
			TextureCubeMap *texture = new TextureCubeMap(pixelTab, tw, th, m_texturesCube.size(), vulkanM);
			m_texturesCube.push_back(texture);
			stbi_image_free(pixel);
			for (int i = 0; i < pixelTab.size(); i++)
			{
				delete(pixelTab[i]);
			}
			vulkanM->str_VulkanDescriptor->textureCubeCount = m_texturesCube.size();
			//updateDescriptor();
			return texture;
		}
		Debug::Warn("Le fichier n'existe pas");
		return nullptr;
	}

	void TextureManager::destroyTexture(Textures *texture)
	{
		m_textures.erase(std::remove(m_textures.begin(), m_textures.end(), texture), m_textures.end());
		delete (texture);
		vulkanM->str_VulkanDescriptor->textureCount = m_textures.size();
		updateDescriptor();
	}
}