#ifndef __ENGINE_MATERIALS__
#define __ENGINE_MATERIALS__

#include "Textures.hpp"
#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "UniformBufferMaterial.hpp"
#include "imgui-cmake/Header/imgui.h"
#include "GraphiquePipeline.hpp"
#include "Component.hpp"

namespace Ge
{
	class Materials : Component
	{
	public:
		Materials(int index, VulkanMisc * vM);
		void setColor(glm::vec3 color);
		void setMetallic(float metal);
		void setHDR(float hdr);
		void setNormal(float normal);
		void setOclusion(float ao);
		void setAlbedoTexture(Textures * albedo);
		void setNormalTexture(Textures * normal);
		void setMetallicTexture(Textures * metal);
		void setHDRTexture(Textures * hdr);
		void setOclusionTexture(Textures * oclu);
		glm::vec3 getColor();
		float getMetallic();
		float getHDR();
		float getNormal();
		float getOclusion();
		Textures * getAlbedoTexture();
		Textures * getNormalTexture();
		Textures * getMetallicTexture();
		Textures * getHDRTexture();
		Textures * getOclusionTexture();
		VkBuffer getUniformBuffers();
		void updateUniformBufferMaterial();
		int getIndex();
		void setIndex(int i);
		void majTextureIndex();
		bool getLightActive();
		void setLightActive(bool state);
		glm::vec2 getOffset();
		void setOffset(glm::vec2 off);
		void setPipeline(GraphiquePipeline * p);
		int getPipelineIndex();
		void onGUI();
		~Materials();
	private:
		UniformBufferMaterial m_ubm{};
		VulkanMisc * vulkanM;
		VmaBuffer m_vmaUniformBuffer;
		Textures * m_albedoMap;
		Textures * m_normalMap;
		Textures * m_metallicMap;
		Textures * m_hdrMap;
		Textures * m_aoMap;
		int m_pipelineIndex;
		float m_color[3];
		float m_offset[2];
		int m_index = 0;
	};
}

#endif//__ENGINE_MATERIALS__