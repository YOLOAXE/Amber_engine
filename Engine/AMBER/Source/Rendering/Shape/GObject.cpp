#include "GObject.hpp"
#include "Debug.hpp"

namespace Ge
{
	GObject::GObject(bool inverse)
	{
		m_inversePos = inverse;
		m_transform.position = glm::vec3(0.0f);
		m_transform.eulerAngles = glm::vec3(0.0f);
		setPosition(glm::vec3(0.0f));
		setEulerAngles(glm::vec3(0.0f));
		setScale(glm::vec3(1.0f));
		m_nom = "NoName";		
	}

	void GObject::setName(std::string name)
	{
		m_nom = name;
	}

	std::string *GObject::getName()
	{
		return &m_nom;
	}

	void GObject::setPosition(glm::vec3 pos)
	{
		float inv = m_inversePos ? -1.0f : 1.0f;
		m_transform.position = pos * inv;
		if (m_flipY)
		{
			m_transform.position.y *= -1.0f;
			m_transform.translateMatrix = glm::translate(glm::mat4(1.0f), m_transform.position);
			m_transform.position = pos;
		}
		else
		{
			m_transform.translateMatrix = glm::translate(glm::mat4(1.0f), m_transform.position);
		}
		mapMemory();
	}

	void GObject::setEulerAngles(glm::vec3 eul)
	{
		m_transform.eulerAngles = eul;
		m_transform.rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_transform.eulerAngles.x * (m_flipY ? -1.0f : 1.0f)), glm::vec3(1.0f, 0.0f, 0.0f));
		m_transform.rotationMatrix = glm::rotate(m_transform.rotationMatrix, glm::radians(m_transform.eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_transform.rotationMatrix = glm::rotate(m_transform.rotationMatrix, glm::radians(m_transform.eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_transform.rotation = toQuat(m_transform.rotationMatrix);
		mapMemory();
	}

	void GObject::setRotation(glm::quat rot)
	{
		m_transform.rotation = rot;
		m_transform.rotationMatrix = toMat4(m_transform.rotation);
		extractEulerAngleXYZ(m_transform.rotationMatrix, m_transform.eulerAngles.x, m_transform.eulerAngles.y, m_transform.eulerAngles.z);
		//TODO attention degrée ou radian
		mapMemory();
	}

	void GObject::setScale(glm::vec3 scale)
	{
		m_transform.scale = scale;
		mapMemory();
	}

	void GObject::setTarget(glm::vec3 target)
	{
		m_transform.target = target;
		m_transform.rotationMatrix = glm::lookAt(m_transform.position, m_transform.target, glm::vec3(0.0f, 0.0f, 1.0f));
		m_transform.rotation = toQuat(m_transform.rotationMatrix);
		extractEulerAngleXYZ(m_transform.rotationMatrix, m_transform.eulerAngles.x, m_transform.eulerAngles.y, m_transform.eulerAngles.z);
		mapMemory();
	}

	glm::vec3 GObject::getPosition()
	{
		float inv = m_inversePos ? -1.0f : 1.0f;
		return m_transform.position * inv;
	}

	glm::quat GObject::getRotation()
	{
		return m_transform.rotation;
	}

	glm::vec3 GObject::getEulerAngles()
	{
		return glm::degrees(m_transform.eulerAngles);
	}

	glm::vec3 GObject::getScale()
	{
		return m_transform.scale;
	}

	glm::vec3 GObject::transformDirectionAxeX()
	{
		glm::vec3 front;
		front.x = -cos(glm::radians(m_transform.eulerAngles.x)) * sin(glm::radians(m_transform.eulerAngles.y));
		front.y = sin(glm::radians(m_transform.eulerAngles.x));
		front.z = cos(glm::radians(m_transform.eulerAngles.x)) * cos(glm::radians(m_transform.eulerAngles.y));
		front = glm::normalize(front);
		return front;
	}

	glm::vec3 GObject::transformDirectionAxeY()
	{
		glm::vec3 front;
		front.x = -cos(glm::radians(m_transform.eulerAngles.x)) * sin(glm::radians(m_transform.eulerAngles.y));
		front.y = sin(glm::radians(m_transform.eulerAngles.x));
		front.z = cos(glm::radians(m_transform.eulerAngles.x)) * cos(glm::radians(m_transform.eulerAngles.y));
		front = glm::normalize(front);
		front = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
		return front;
	}

	glm::vec3 GObject::transformDirectionAxeZ()
	{
		glm::vec3 front;
		front.x = -cos(glm::radians(m_transform.eulerAngles.x)) * sin(glm::radians(m_transform.eulerAngles.y));
		front.y = sin(glm::radians(m_transform.eulerAngles.x));
		front.z = cos(glm::radians(m_transform.eulerAngles.x)) * cos(glm::radians(m_transform.eulerAngles.y));
		front = glm::normalize(front);
		front = glm::normalize(glm::cross(front, glm::vec3(1.0f, 0.0f, 0.0f)));
		return front;
	}

	glm::vec3 GObject::transformDirectionAxe(glm::vec3 dir)
	{
		glm::vec3 front;
		front.x = -cos(glm::radians(m_transform.eulerAngles.x)) * sin(glm::radians(m_transform.eulerAngles.y));
		front.y = sin(glm::radians(m_transform.eulerAngles.x));
		front.z = cos(glm::radians(m_transform.eulerAngles.x)) * cos(glm::radians(m_transform.eulerAngles.y));
		front = glm::normalize(front);
		front = glm::normalize(glm::cross(front, glm::vec3(dir.x, dir.y, dir.z)));
		return front;
	}

	bool GObject::getFlipY()
	{
		return m_flipY;
	}

	void GObject::setFlipY(bool state)
	{
		m_flipY = state;
		setPosition(getPosition());
		setRotation(getRotation());
	}

	void GObject::mapMemory(){}

	void GObject::addComponent(Component *c)
	{
		//TODO Component
	}

	void GObject::removeComponent(Component *c)
	{
	}

	void GObject::onGUI()
	{
		if (ImGui::DragFloat3("Position", (float *)&m_transform.position, 0.2f))
		{
			setPosition(m_transform.position);
		}

		if (ImGui::DragFloat3("EulerAngles", (float *)&m_transform.eulerAngles, 0.2f))
		{
			setEulerAngles(m_transform.eulerAngles);
		}

		if (ImGui::DragFloat4("Rotation", (float *)&m_transform.rotation, 0.2f))
		{
			setRotation(m_transform.rotation);
		}

		if (ImGui::DragFloat3("Scale", (float *)&m_transform.scale, 0.2f))
		{
			setScale(m_transform.scale);
		}

		if (m_Component.size() > 0)
		{
			for (Component *comp : m_Component)
			{
				comp->onGUI();
			}
		}
	}
}