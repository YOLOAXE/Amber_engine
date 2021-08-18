#ifndef __ENGINE_LIGHT__
#define __ENGINE_LIGHT__

#include "Light.hpp"
#include "Vector3.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/common.hpp"
#include "UniformBufferLight.hpp"
#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "BufferManager.hpp"
#include "GObject.hpp"
#include "ImGUiUBL.hpp"

namespace Ge
{
	class Lights : virtual public Light, public GObject
	{
	public:
		Lights(int index, VulkanMisc *vM);
		void setColors(Vector3 color);
		Vector3 getColors();
		void setSpecular(Vector3 spec);
		Vector3 getSpecular();
		Vector3 getDirection();
		void setDirection(Vector3 direction);
		void setEulerAngles(Vector3 eul) override;
		Vector3 getEulerAngles() override;
		Vector3 getPosition() override;
		void setPosition(Vector3 pos) override;
		void setAmbiant(Vector3 ambiant);
		int getStatus();
		Vector3 getAmbiant();
		int getIndex();
		void setIndex(int i);
		VkBuffer getUniformBuffers();
		VkBuffer getlightMatrixShadowUniformBuffers();		
		void updateUniformBufferLight();
		void onGUI() override;
		virtual ~Lights();

	protected:
		UniformBufferLight m_ubl{};
		ImGUiUBL m_imGUiUBL{};
		VulkanMisc *vMisc;
		VmaBuffer m_vmaUniformBuffer;
		VmaBuffer m_vmaOffScreenShadowBuffer;
		float m_nearPlane = 1.0f;
		float m_farPlane = 7.5f;
		int m_index = 0;
		bool m_shadow = false;
	};
}

#endif //__ENGINE_LIGHT__
