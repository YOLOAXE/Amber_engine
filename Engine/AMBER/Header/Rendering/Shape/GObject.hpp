#ifndef __ENGINE_GRAPHIC_OBJECT__
#define __ENGINE_GRAPHIC_OBJECT__

#include "Transform.hpp"
#include "Debug.hpp"
#include "Component.hpp"
#include "imgui-cmake/Header/imgui.h"
#include <vector>
#include <string> 

namespace Ge
{
	class GObject
	{
	public:
		GObject(bool inverse = false);
		void setName(std::string nom);
		std::string * getName();
		void setPosition(glm::vec3 pos);
		void setRotation(glm::quat rot);
		void setEulerAngles(glm::vec3 eul);
		void setScale(glm::vec3 scale);
		void setTarget(glm::vec3 target);
		glm::vec3 getPosition();
		glm::quat getRotation();
		glm::vec3 getEulerAngles();
		glm::vec3 getScale();
		virtual void mapMemory(); // map matrice pour les exporter dans les descriptors
		glm::vec3 transformDirectionAxeX();
		glm::vec3 transformDirectionAxeY();
		glm::vec3 transformDirectionAxeZ();
		glm::vec3 transformDirectionAxe(glm::vec3 dir);
		bool getFlipY();
		void setFlipY(bool state);
		void addComponent(Component * c);
		void removeComponent(Component * c);
		virtual void onGUI();
	protected:
		std::vector<GObject *> m_childs;//implementer
		std::string m_nom;
		bool m_flipY = false;
		bool m_inversePos = true;
		Transform m_transform{};
		std::vector<Component *> m_Component;
	};
}

#endif //__ENGINE_GRAPHIC_OBJECT__