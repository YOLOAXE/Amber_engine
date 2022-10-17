#include "GObject.hpp"

namespace Ge
{
	std::vector<GObject *> GObject::s_gobjects;
	GObject::GObject()
	{
		m_nom = "NoName";
		s_gobjects.push_back(this);
	}

	GObject::~GObject()
	{
		s_gobjects.erase(std::remove(s_gobjects.begin(), s_gobjects.end(), this), s_gobjects.end());
	}

	std::vector<GObject *> GObject::GetGObjects()
	{
		return s_gobjects;
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
		m_transform.position = pos;
		m_transform.translateMatrix = glm::translate(glm::mat4(1.0f), m_transform.position);
		mapMemory();
	}

	void GObject::setEulerAngles(glm::vec3 eul)
	{
		m_transform.eulerAngles = eul;
		float yaw = glm::radians(m_transform.eulerAngles.x);
		float pitch = glm::radians(m_transform.eulerAngles.y);
		float roll = glm::radians(m_transform.eulerAngles.z);
		m_transform.rotationMatrix = glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(1.0f, 0.0f, 0.0f));
		m_transform.rotationMatrix = glm::rotate(m_transform.rotationMatrix, pitch, glm::vec3(0.0f, 1.0f, 0.0f));
		m_transform.rotationMatrix = glm::rotate(m_transform.rotationMatrix, roll, glm::vec3(0.0f, 0.0f, 1.0f));
		m_transform.rotation = toQuat(m_transform.rotationMatrix);
		m_transform.direction.x = sin(yaw);
		m_transform.direction.y = -(sin(pitch)*cos(yaw));
		m_transform.direction.z = -(cos(pitch)*cos(yaw));
		mapMemory();
	}

	void GObject::setRotation(glm::quat rot)
	{
		m_transform.rotation = rot;
		m_transform.rotationMatrix = toMat4(m_transform.rotation);
		extractEulerAngleXYZ(m_transform.rotationMatrix, m_transform.eulerAngles.x, m_transform.eulerAngles.y, m_transform.eulerAngles.z);
		m_transform.direction.x = sin(m_transform.eulerAngles.x);
		m_transform.direction.y = -(sin(m_transform.eulerAngles.y)*cos(m_transform.eulerAngles.x));
		m_transform.direction.z = -(cos(m_transform.eulerAngles.y)*cos(m_transform.eulerAngles.x));
		m_transform.eulerAngles = glm::degrees(m_transform.eulerAngles);
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
		float yaw = glm::radians(m_transform.eulerAngles.x);
		float pitch = glm::radians(m_transform.eulerAngles.y);
		float roll = glm::radians(m_transform.eulerAngles.z);
		m_transform.direction.x = sin(yaw);
		m_transform.direction.y = -(sin(pitch)*cos(yaw));
		m_transform.direction.z = -(cos(pitch)*cos(yaw));
		mapMemory();
	}

	glm::vec3 GObject::getPosition()
	{
		return m_transform.position;
	}

	glm::quat GObject::getRotation()
	{
		return m_transform.rotation;
	}

	glm::vec3 GObject::getEulerAngles()
	{
		return glm::degrees(m_transform.eulerAngles);
	}

	glm::vec3 GObject::getDirection()
	{
		return m_transform.direction;
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
		return false;
	}

	void GObject::setFlipY(bool state)
	{
		setPosition(getPosition());
		setRotation(getRotation());
	}

	void GObject::addComponent(Component *c)
	{
		m_component.push_back(c);
	}

	void GObject::removeComponent(Component *c)
	{
		m_component.erase(std::remove(m_component.begin(), m_component.end(), c), m_component.end());
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

		if (ImGui::DragFloat3("Direction", (float *)&m_transform.direction, 0.2f))
		{
			//setScale(m_transform.scale);
		}

		for (Component *comp : m_component)
		{
			comp->onGUI();
		}
	}
}