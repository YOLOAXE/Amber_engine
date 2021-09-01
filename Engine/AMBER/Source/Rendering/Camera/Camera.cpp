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
			m_uniformBufferCamera.proj = glm::perspective(glm::radians(m_fov), vulkanM->str_VulkanSwapChainMisc->str_swapChainExtent.height/ (float)vulkanM->str_VulkanSwapChainMisc->str_swapChainExtent.height, m_near, m_far);
		}
		m_uniformBufferCamera.proj[1][1] *= -1;
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_uniformBufferCamera, sizeof(m_uniformBufferCamera));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	Camera::Camera(VulkanMisc * vM) : GObject(true)
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
		m_uniformBufferCamera.camPos = m_transform.position;
		m_uniformBufferCamera.view = m_transform.rotationMatrix * m_transform.translateMatrix;
		Camera::updatePerspective();
	}	

	Camera::~Camera()
	{		
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
	}

	void Camera::mapMemory()
	{		
		m_uniformBufferCamera.camPos = m_transform.position;
		m_uniformBufferCamera.view = m_transform.rotationMatrix * m_transform.translateMatrix;
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_uniformBufferCamera, sizeof(m_uniformBufferCamera));
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

	glm::mat4 Camera::getView()
	{
		m_uniformBufferCamera.view = m_transform.rotationMatrix * m_transform.translateMatrix;
		return m_uniformBufferCamera.view;
	}

	glm::mat4 Camera::getProjection()
	{
		return m_uniformBufferCamera.proj;
	}
}