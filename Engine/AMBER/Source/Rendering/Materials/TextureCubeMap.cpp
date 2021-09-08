#include "TextureCubeMap.hpp"
#include "ImageViewSwapChains.hpp"

namespace Ge
{
	TextureCubeMap::TextureCubeMap(std::vector<unsigned char *> pc, int Width, int Height, int ind, VulkanMisc * vM)
	{
		index = ind;
		vulkanM = vM->str_VulkanDeviceMisc;
		texHeight = Height/3;
		texWidth = Width/4;
		imageSize = texWidth * texHeight * 4 * 6;
		mipLevels = 1;//static_cast<uint32_t>(std::floor(std::log2(Width > Height ? Width : Height))) + 1;
		VmaBuffer stagingBuffer;
		BufferManager::createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, vM->str_VulkanDeviceMisc);
		
		void * data = BufferManager::mapMemory(stagingBuffer);
		VkDeviceSize layersize = imageSize / 6;
		for (int face = 0; face < 6; face++)
		{
			memcpy((stbi_uc *)data + (layersize)*face, pc[face], static_cast<size_t>(layersize));
		}
		BufferManager::unMapMemory(stagingBuffer);

		BufferManager::createImageBuffer(texWidth, texHeight, VK_IMAGE_TYPE_2D,6, 1, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT, vM);

		Textures::transitionImageLayout(textureImage.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels, vM);//VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
		BufferManager::copyBufferToImage(stagingBuffer.buffer, textureImage.image, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight), vM);
		BufferManager::destroyBuffer(stagingBuffer);

		Textures::generateMipmaps(textureImage.image, VK_FORMAT_R8G8B8A8_UNORM, texWidth, texHeight, mipLevels, 6, vM);

		VkImageViewCreateInfo viewInfo{};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
		viewInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
		viewInfo.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };
		viewInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
		viewInfo.subresourceRange.layerCount = 6;
		viewInfo.subresourceRange.levelCount = mipLevels;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.image = textureImage.image;

		if (vkCreateImageView(vM->str_VulkanDeviceMisc->str_device, &viewInfo, nullptr, &textureImageView) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'une image vue");
		}

		VkSamplerCreateInfo samplerInfo{};
		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerInfo.magFilter = VK_FILTER_LINEAR;
		samplerInfo.minFilter = VK_FILTER_LINEAR;
		samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		samplerInfo.mipLodBias = 0.0f;
		samplerInfo.compareOp = VK_COMPARE_OP_NEVER;
		samplerInfo.minLod = 0.0f;
		samplerInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
		samplerInfo.maxAnisotropy = 1.0f;
		samplerInfo.maxLod = static_cast<float>(mipLevels);
		if (vkCreateSampler(vM->str_VulkanDeviceMisc->str_device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS)
		{
			Debug::Error("Echec de la creation d'un sampler de texture");
		}
	}
	

	TextureCubeMap::~TextureCubeMap()
	{
		vkDestroySampler(vulkanM->str_device, textureSampler, nullptr);
		vkDestroyImageView(vulkanM->str_device, textureImageView, nullptr);
		BufferManager::destroyImageBuffer(textureImage);
	}

	int TextureCubeMap::getIndex()
	{
		return index;
	}

	VkImageView TextureCubeMap::getVkImageView()
	{
		return textureImageView;
	}

	VkSampler TextureCubeMap::getVkSampler()
	{
		return textureSampler;
	}
}