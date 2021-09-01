#ifndef __ENGINE_MATERIALS__
#define __ENGINE_MATERIALS__

#include "Material.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Textures.hpp"
#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "UniformBufferMaterial.hpp"
#include "imgui-cmake/Header/imgui.h"

namespace Ge
{
	class Materials : public Material
	{
	public:
		Materials(int index, VulkanMisc * vM);
		void setColor(Vector3 color);
		void setMetallic(float metal);
		void setHDR(float hdr);
		void setNormal(float normal);
		void setOclusion(float ao);
		void setAlbedoTexture(Texture * albedo);
		void setNormalTexture(Texture * normal);
		void setMetallicTexture(Texture * metal);
		void setHDRTexture(Texture * hdr);
		void setOclusionTexture(Texture * oclu);
		Vector3 getColor();
		float getMetallic();
		float getHDR();
		float getNormal();
		float getOclusion();
		Texture * getAlbedoTexture();
		Texture * getNormalTexture();
		Texture * getMetallicTexture();
		Texture * getHDRTexture();
		Texture * getOclusionTexture();
		VkBuffer getUniformBuffers();
		void updateUniformBufferMaterial();
		int getIndex();
		void setIndex(int i);
		void majTextureIndex();
		bool getLightActive();
		void setLightActive(bool state);
		Vector2 getOffset();
		void setOffset(Vector2 off);
		void setPipeline(Pipeline * p);
		int getPipelineIndex();
		void onGUI();
		~Materials();
	private:
		UniformBufferMaterial m_ubm{};
		VulkanMisc * vulkanM;
		VmaBuffer m_vmaUniformBuffer;
		Texture * m_albedoMap;
		Texture * m_normalMap;
		Texture * m_metallicMap;
		Texture * m_hdrMap;
		Texture * m_aoMap;
		int m_pipelineIndex;
		float m_color[3];
		float m_offset[2];
		int m_index = 0;
	};
}

#endif//__ENGINE_MATERIALS__