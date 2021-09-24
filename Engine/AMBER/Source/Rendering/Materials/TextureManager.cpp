#include "TextureManager.hpp"
namespace fs = std::filesystem;

namespace Ge
{
	TextureCubeMap * TextureManager::s_nullTextureCubeMap = nullptr;
	bool TextureManager::initialize(VulkanMisc *vM)
	{
		vulkanM = vM;
		stbi_uc *pixel = new stbi_uc[48];
		for (int i = 0; i < 48; i++)
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

	std::vector<unsigned char *> TextureManager::convertCubMap(unsigned char * pixel, int tw, int th)//hauter 3 largeur 4
	{
		int twCubeMap = tw/4;
		int thCubeMap = th/3;
		std::vector<unsigned char *> pixelTab;
		std::vector<int> indiceStbi;
		std::vector<unsigned char *> pixelTabCubeMap;		
		int indiceCubeMap[6] = { 6 , 4 , 1 , 9 , 5, 7 };
		for (int i = 0; i < 12; i++)
		{
			pixelTab.push_back(new stbi_uc[twCubeMap * thCubeMap*4]);//4 char * -> 1			
		}
		indiceStbi.resize(12);
		int indicePT = 0,indicePixel = 0;
		for (int y = 0; y < th; y++)
		{
			for (int x = 0; x < tw; x++)
			{
				indicePT = (x / twCubeMap)+((y/ thCubeMap)*4);
				if (std::find(std::begin(indiceCubeMap), std::end(indiceCubeMap), indicePT) != std::end(indiceCubeMap))
				{
					pixelTab[indicePT][indiceStbi[indicePT] + 0] = pixel[indicePixel + 0];
					pixelTab[indicePT][indiceStbi[indicePT] + 1] = pixel[indicePixel + 1];
					pixelTab[indicePT][indiceStbi[indicePT] + 2] = pixel[indicePixel + 2];
					pixelTab[indicePT][indiceStbi[indicePT] + 3] = pixel[indicePixel + 3];
					indiceStbi[indicePT] += 4;				
					indicePixel += 4;
				}		
				else
				{					
					indicePixel += twCubeMap *4;
					x += twCubeMap-1;
				}				
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