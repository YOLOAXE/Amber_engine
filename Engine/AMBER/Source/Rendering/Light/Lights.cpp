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
		setPosition(glm::vec3(0.0f));
		setEulerAngles(glm::vec3(0.0f));
		setScale(glm::vec3(1.0f));
	}

	void Lights::mapMemory()
	{
		m_ubl.position = m_transform.position;
		m_ubl.direction = glm::vec3(0, 0, 0);//todo ajouter la direction
		updateUniformBufferLight();
	}

	void Lights::setColors(glm::vec3 color)
	{
		m_ubl.diffuse = color;
		updateUniformBufferLight();
	}

	glm::vec3 Lights::getColors()
	{
		return m_ubl.diffuse;
	}

	void Lights::setSpecular(glm::vec3 spec)
	{
		m_ubl.specular = spec;
		updateUniformBufferLight();
	}

	glm::vec3 Lights::getSpecular()
	{
		return m_ubl.specular;
	}

	void Lights::setAmbiant(glm::vec3 ambiant)
	{
		m_ubl.ambient = ambiant;
		updateUniformBufferLight();
	}

	int Lights::getStatus()
	{
		return m_ubl.status;
	}

	glm::vec3 Lights::getAmbiant()
	{
		return m_ubl.ambient;
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
		GObject::onGUI();
		ImGui::TextColored(ImVec4(0.2f, 1, 0.2f, 1), "Light\n");
		if (ImGui::ColorEdit3("Color", (float *)&m_ubl.diffuse))
		{
			setColors(m_ubl.diffuse);
		}
		if (ImGui::ColorEdit3("Ambiant", (float *)&m_ubl.ambient))
		{
			setAmbiant(m_ubl.ambient);
		}
		if (ImGui::ColorEdit3("Specular", (float *)&m_ubl.specular))
		{
			setSpecular(m_ubl.specular);
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