#include "Camera.hpp"
#include "CameraManager.hpp"

namespace Ge
{
	void Camera::updatePerspective()
	{
		if (m_ortho)
		{		
			m_uniformBufferCamera.proj = glm::ortho(0.0f, (float)vulkanM->str_VulkanSwapChainMisc->str_swapChainExtent.width, (float)vulkanM->str_VulkanSwapChainMisc->str_swapChainExtent.height, 0.0f, m_near, m_far);
		}
		else
		{
			m_uniformBufferCamera.proj = glm::perspective(glm::radians(m_fov), 16.0f/9.0f, m_near, m_far);
		}
		m_uniformBufferCamera.proj[1][1] *= -1;
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_uniformBufferCamera, sizeof(UniformBufferCamera));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	Camera::Camera(VulkanMisc * vM) : GObject(false)
	{
		if (!BufferManager::createBuffer(sizeof(UniformBufferCamera), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc)) 
		{
			Debug::Error("Echec de la creation d'un uniform buffer object");
		}
		m_far = 500.0f;
		m_fov = 70.0f;
		m_near = 0.1f;
		m_priority = 0;
		vulkanM = vM;
		m_ortho = false;
		m_uniformBufferCamera.camPos = m_transform.position;
		m_uniformBufferCamera.view = m_transform.rotationMatrix * m_transform.translateMatrix;
		Camera::updatePerspective();	
		setPosition(glm::vec3(0.0f));
		setEulerAngles(glm::vec3(0.0f));
		setScale(glm::vec3(1.0f));
	}	

	Camera::~Camera()
	{		
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
	}

	void Camera::mapMemory()
	{		
		m_uniformBufferCamera.camPos = m_transform.position;
		m_uniformBufferCamera.view = m_transform.rotationMatrix * m_transform.translateMatrix;
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_uniformBufferCamera, sizeof(UniformBufferCamera));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	VkBuffer Camera::getUniformBuffer()
	{
		return m_vmaUniformBuffer.buffer;
	}

	void Camera::setFieldOfView(float fov)
	{
		m_fov = fov;
		Camera::updatePerspective();
	}

	void Camera::setNear(float n)
	{
		m_near = n;
		Camera::updatePerspective();
	}

	void Camera::setFar(float f)
	{
		m_far = f;
		Camera::updatePerspective();
	}

	void Camera::setPriority(int p)
	{
		m_priority = p;
		CameraManager::updatePriorityCamera();
	}

	void Camera::setOrtho(bool state)
	{
		m_ortho = state;
		Camera::updatePerspective();
	}

	float Camera::getFieldOfView()
	{
		return m_fov;
	}

	float Camera::getNear()
	{
		return m_near;
	}

	float Camera::getFar()
	{
		return m_far;
	}

	int Camera::getPriority()
	{
		return m_priority;
	}

	void Camera::onGUI()
	{
		GObject::onGUI();
		ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Camera\n");
		if (ImGui::DragFloat("Fov", &m_fov,2.0f,10.0f,180.0f))
		{
			Camera::updatePerspective();
		}
		if (ImGui::DragFloat("Near", &m_near, 0.5f, 0.0001f, 10.0f))
		{
			Camera::updatePerspective();
		}
		if (ImGui::DragFloat("Far", &m_far, 0.5f, 1.0f, 10000.0f))
		{
			Camera::updatePerspective();
		}
		if (ImGui::DragInt("Priority", &m_priority, 1.0f))
		{
			CameraManager::updatePriorityCamera();
		}
		if (ImGui::Checkbox("Ortho", &m_ortho))
		{
			Camera::updatePerspective();
		}

	}
}