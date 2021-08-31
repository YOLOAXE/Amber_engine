#include "Lights.hpp"

namespace Ge
{
	Lights::Lights(int index, VulkanMisc * vM) : GObject()
	{
		vMisc = vM;
		m_index = index;
		m_ubl.position = glm::vec3(0, 0, 0);
		m_ubl.diffuse = glm::vec3(0, 0, 0);
		m_ubl.specular = glm::vec3(0.0f);
		m_ubl.ambient = glm::vec3(0.1f);
		if (!BufferManager::createBuffer(sizeof(UniformBufferLight), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffer, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer object");
		}		
		updateUniformBufferLight();
	}

	void Lights::setColors(Vector3 color)
	{
		m_ubl.diffuse = glm::vec3(color.x, color.y, color.z);
		updateUniformBufferLight();
	}

	Vector3 Lights::getColors()
	{
		return Vector3(m_ubl.diffuse.x, m_ubl.diffuse.y, m_ubl.diffuse.z);
	}

	void Lights::setSpecular(Vector3 spec)
	{
		m_ubl.specular = glm::vec3(spec.x, spec.y, spec.z);
		updateUniformBufferLight();
	}

	Vector3 Lights::getSpecular()
	{
		return Vector3(m_ubl.specular.x, m_ubl.specular.y, m_ubl.specular.z);
	}

	void Lights::setEulerAngles(Vector3 eul)
	{
		m_ubl.direction = glm::vec3(eul.x, eul.y, eul.z);
		m_transform.eul = eul;//A changer
		m_transform.eulerAngles = m_ubl.direction;//A changer	
		updateUniformBufferLight();//TODO verifier les a changer
	}

	Vector3 Lights::getEulerAngles()
	{
		return m_transform.eul;
	}

	Vector3 Lights::getPosition()
	{
		return Vector3(m_ubl.position.x, m_ubl.position.y, m_ubl.position.z);
	}

	void Lights::setPosition(Vector3 position)
	{
		m_ubl.position = glm::vec3(position.x, position.y, position.z);
		m_transform.position = m_ubl.position;
		m_transform.pos = position;	
		updateUniformBufferLight();
	}

	void Lights::setAmbiant(Vector3 ambiant)
	{
		m_ubl.ambient = glm::vec3(ambiant.x, ambiant.y, ambiant.z);
		updateUniformBufferLight();
	}

	int Lights::getStatus()
	{
		return m_ubl.status;
	}

	Vector3 Lights::getAmbiant()
	{
		return Vector3(m_ubl.ambient.x, m_ubl.ambient.y, m_ubl.ambient.z);
	}

	int Lights::getIndex()
	{
		return m_index;
	}

	void Lights::setIndex(int i)
	{
		m_index = i;
	}

	VkBuffer Lights::getUniformBuffers()
	{
		return m_vmaUniformBuffer.buffer;
	}

	void Lights::setShadow(bool state)
	{

	}

	bool Lights::getShadow()
	{
		return false;//TODO réaliser la Shadow
	}


	void Lights::updateUniformBufferLight()
	{
		memcpy(BufferManager::mapMemory(m_vmaUniformBuffer), &m_ubl, sizeof(m_ubl));
		BufferManager::unMapMemory(m_vmaUniformBuffer);
	}

	void Lights::onGUI()
	{
		m_imGUiUBL.ambient[0] = m_ubl.ambient.x;
		m_imGUiUBL.ambient[1] = m_ubl.ambient.y;
		m_imGUiUBL.ambient[2] = m_ubl.ambient.z;

		m_imGUiUBL.diffuse[0] = m_ubl.diffuse.x;
		m_imGUiUBL.diffuse[1] = m_ubl.diffuse.y;
		m_imGUiUBL.diffuse[2] = m_ubl.diffuse.z;

		m_imGUiUBL.specular[0] = m_ubl.specular.x;
		m_imGUiUBL.specular[1] = m_ubl.specular.y;
		m_imGUiUBL.specular[2] = m_ubl.specular.z;

		GObject::onGUI();
		ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Light\n");
		if (ImGui::ColorEdit3("Color", m_imGUiUBL.diffuse))
		{
			setColors(Vector3(m_imGUiUBL.diffuse[0], m_imGUiUBL.diffuse[1], m_imGUiUBL.diffuse[2]));
		}
		if (ImGui::ColorEdit3("Ambiant", m_imGUiUBL.ambient))
		{
			setAmbiant(Vector3(m_imGUiUBL.ambient[0], m_imGUiUBL.ambient[1], m_imGUiUBL.ambient[2]));
		}
		if (ImGui::ColorEdit3("Specular", m_imGUiUBL.specular))
		{
			setSpecular(Vector3(m_imGUiUBL.specular[0], m_imGUiUBL.specular[1], m_imGUiUBL.specular[2]));
		}
		ImGui::DragFloat("Quadratic", &m_ubl.quadratic,0.1f);
		ImGui::DragFloat("Constant", &m_ubl.constant,0.1f);
		ImGui::DragFloat("Linear", &m_ubl.linear,0.1f);
		if (m_ubl.status == 2)
		{
			ImGui::DragFloat("CutOff", &m_ubl.cutOff,0.2f);
			ImGui::DragFloat("OuterCutOff", &m_ubl.outerCutOff,0.2f);
		}
	}

	Lights::~Lights()
	{		
		BufferManager::destroyBuffer(m_vmaUniformBuffer);
	}
}