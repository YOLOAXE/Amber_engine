#include "GObject.hpp"
#include "Debug.hpp"

namespace Ge
{
	GObject::GObject(bool inverse)
	{
		m_inversePos = inverse;
		m_transform.position = glm::vec3(0.0f);
		m_transform.eulerAngles = glm::vec3(0.0f);
		setPosition(Vector3(0.0f));
		setEulerAngles(Vector3(0.0f));
		setScale(Vector3(1.0f));
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

	void GObject::setPosition(Vector3 pos)
	{
		float inv = m_inversePos ? -1.0f : 1.0f;
		m_transform.position.x = pos.x * inv;
		m_transform.position.y = pos.y * inv;
		m_transform.position.z = pos.z * inv;
		m_transform.pos = pos * inv;
		if (m_flipY)
		{
			m_transform.position.y *= -1.0f;
			m_transform.translateMatrix = glm::translate(glm::mat4(1.0f), m_transform.position);
			m_transform.position.x = pos.x;
			m_transform.position.y = pos.y;
			m_transform.position.z = pos.z;
		}
		else
		{
			m_transform.translateMatrix = glm::translate(glm::mat4(1.0f), m_transform.position);
		}
		mapMemory();
	}

	void GObject::setEulerAngles(Vector3 eul)
	{
		m_transform.eulerAngles.x = eul.x;
		m_transform.eulerAngles.y = eul.y;
		m_transform.eulerAngles.z = eul.z;
		m_transform.eul = eul;
		m_transform.rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_transform.eulerAngles.x * (m_flipY ? -1.0f : 1.0f)), glm::vec3(1.0f, 0.0f, 0.0f));
		m_transform.rotationMatrix = glm::rotate(m_transform.rotationMatrix, glm::radians(m_transform.eulerAngles.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_transform.rotationMatrix = glm::rotate(m_transform.rotationMatrix, glm::radians(m_transform.eulerAngles.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_transform.rotation = toQuat(m_transform.rotationMatrix);
		mapMemory();
	}

	void GObject::setRotation(Vector4 rot)
	{
		m_transform.rotation.x = rot.x;
		m_transform.rotation.y = rot.y;
		m_transform.rotation.z = rot.z;
		m_transform.rotation.w = rot.w;
		m_transform.rot = rot;
		m_transform.rotationMatrix = toMat4(m_transform.rotation);
		extractEulerAngleXYZ(m_transform.rotationMatrix, m_transform.eulerAngles.x, m_transform.eulerAngles.y, m_transform.eulerAngles.z);
		mapMemory();
	}

	void GObject::setScale(Vector3 scale)
	{
		m_transform.scale.x = scale.x;
		m_transform.scale.y = scale.y;
		m_transform.scale.z = scale.z;
		m_transform.size = scale;
		mapMemory();
	}

	void GObject::setTarget(Vector3 target)
	{
		m_transform.target = glm::vec3(target.x, target.y, target.z);
		m_transform.rotationMatrix = glm::lookAt(m_transform.position, m_transform.target, glm::vec3(0.0f, 0.0f, 1.0f));
		m_transform.rotation = toQuat(m_transform.rotationMatrix);
		extractEulerAngleXYZ(m_transform.rotationMatrix, m_transform.eulerAngles.x, m_transform.eulerAngles.y, m_transform.eulerAngles.z);
		mapMemory();
	}

	Vector3 GObject::getPosition()
	{
		float inv = m_inversePos ? -1.0f : 1.0f;
		return m_transform.pos * inv;
	}

	Vector4 GObject::getRotation()
	{
		m_transform.rotation = toQuat(m_transform.rotationMatrix);
		m_transform.rot.x = m_transform.rotation.x;
		m_transform.rot.y = m_transform.rotation.y;
		m_transform.rot.z = m_transform.rotation.z;
		m_transform.rot.w = m_transform.rotation.w;

		return m_transform.rot;
	}

	Vector3 GObject::getEulerAngles()
	{

		extractEulerAngleXYZ(m_transform.rotationMatrix, m_transform.eulerAngles.x, m_transform.eulerAngles.y, m_transform.eulerAngles.z);
		m_transform.eulerAngles = glm::degrees(m_transform.eulerAngles);
		m_transform.eul.x = m_transform.eulerAngles.x;
		m_transform.eul.y = m_transform.eulerAngles.y;
		m_transform.eul.z = m_transform.eulerAngles.z;

		return m_transform.eul;
	}

	Vector3 GObject::getScale()
	{
		return m_transform.size;
	}

	Vector3 GObject::transformDirectionAxeX()
	{
		getEulerAngles();
		glm::vec3 front;
		front.x = -cos(glm::radians(m_transform.eulerAngles.x)) * sin(glm::radians(m_transform.eulerAngles.y));
		front.y = sin(glm::radians(m_transform.eulerAngles.x));
		front.z = cos(glm::radians(m_transform.eulerAngles.x)) * cos(glm::radians(m_transform.eulerAngles.y));
		front = glm::normalize(front);
		return Vector3(front.x, front.y, front.z);
	}

	Vector3 GObject::transformDirectionAxeY()
	{
		getEulerAngles();
		glm::vec3 front;
		front.x = -cos(glm::radians(m_transform.eulerAngles.x)) * sin(glm::radians(m_transform.eulerAngles.y));
		front.y = sin(glm::radians(m_transform.eulerAngles.x));
		front.z = cos(glm::radians(m_transform.eulerAngles.x)) * cos(glm::radians(m_transform.eulerAngles.y));
		front = glm::normalize(front);
		front = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
		return Vector3(front.x, front.y, front.z);
	}

	Vector3 GObject::transformDirectionAxeZ()
	{
		getEulerAngles();
		glm::vec3 front;
		front.x = -cos(glm::radians(m_transform.eulerAngles.x)) * sin(glm::radians(m_transform.eulerAngles.y));
		front.y = sin(glm::radians(m_transform.eulerAngles.x));
		front.z = cos(glm::radians(m_transform.eulerAngles.x)) * cos(glm::radians(m_transform.eulerAngles.y));
		front = glm::normalize(front);
		front = glm::normalize(glm::cross(front, glm::vec3(1.0f, 0.0f, 0.0f)));
		return Vector3(front.x, front.y, front.z);
	}

	Vector3 GObject::transformDirectionAxe(Vector3 dir)
	{
		getEulerAngles();
		glm::vec3 front;
		front.x = -cos(glm::radians(m_transform.eulerAngles.x)) * sin(glm::radians(m_transform.eulerAngles.y));
		front.y = sin(glm::radians(m_transform.eulerAngles.x));
		front.z = cos(glm::radians(m_transform.eulerAngles.x)) * cos(glm::radians(m_transform.eulerAngles.y));
		front = glm::normalize(front);
		front = glm::normalize(glm::cross(front, glm::vec3(dir.x, dir.y, dir.z)));
		return Vector3(front.x, front.y, front.z);
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

	void GObject::mapMemory()
	{
	}

	void GObject::addComponent(Component *c)
	{
	}

	void GObject::removeComponent(Component *c)
	{
	}

	void GObject::onGUI()
	{
		m_transformImgui.pos[0] = m_transform.pos.x;
		m_transformImgui.pos[1] = m_transform.pos.y;
		m_transformImgui.pos[2] = m_transform.pos.z;

		m_transformImgui.rot[0] = m_transform.rotation.x;
		m_transformImgui.rot[1] = m_transform.rotation.y;
		m_transformImgui.rot[2] = m_transform.rotation.z;
		m_transformImgui.rot[3] = m_transform.rotation.w;

		m_transformImgui.eul[0] = m_transform.eulerAngles.x;
		m_transformImgui.eul[1] = m_transform.eulerAngles.y;
		m_transformImgui.eul[2] = m_transform.eulerAngles.z;

		m_transformImgui.size[0] = m_transform.size.x;
		m_transformImgui.size[1] = m_transform.size.y;
		m_transformImgui.size[2] = m_transform.size.z;

		if (ImGui::DragFloat3("Position", &m_transformImgui.pos[0], 0.2f))
		{
			setPosition(Vector3(m_transformImgui.pos[0], m_transformImgui.pos[1], m_transformImgui.pos[2]));
		}

		if (ImGui::DragFloat3("EulerAngles", &m_transformImgui.eul[0], 0.2f))
		{
			setEulerAngles(Vector3(m_transformImgui.eul[0], m_transformImgui.eul[1], m_transformImgui.eul[2]));
		}

		if (ImGui::DragFloat4("Rotation", &m_transformImgui.rot[0], 0.2f))
		{
			setRotation(Vector4(m_transformImgui.rot[0], m_transformImgui.rot[1], m_transformImgui.rot[2], m_transformImgui.rot[3]));
		}

		if (ImGui::DragFloat3("Scale", &m_transformImgui.size[0], 0.2f))
		{
			setScale(Vector3(m_transformImgui.size[0], m_transformImgui.size[1], m_transformImgui.size[2]));
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