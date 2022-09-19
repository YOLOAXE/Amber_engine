#ifndef __ENGINE_GRAPHIC_OBJECT__
#define __ENGINE_GRAPHIC_OBJECT__

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/common.hpp"
#include "Debug.hpp"
#include "Component.hpp"
#include "imgui-cmake/Header/imgui.h"
#include "Transform.hpp"
#include <vector>
#include <string> 
#include <algorithm>

namespace Ge
{
	class GObject
	{
	public:
		GObject(bool inverse = false);
		~GObject();
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
		glm::vec3 getDirection();
		glm::vec3 getScale();
		virtual void mapMemory() = 0;
		glm::vec3 transformDirectionAxeX();
		glm::vec3 transformDirectionAxeY();
		glm::vec3 transformDirectionAxeZ();
		glm::vec3 transformDirectionAxe(glm::vec3 dir);
		bool getFlipY();
		void setFlipY(bool state);
		void addComponent(Component * c);
		void removeComponent(Component * c);
		static std::vector<GObject *> GetGObjects();
		virtual void onGUI();
	protected:
		static std::vector<GObject *> s_gobjects;
		std::vector<GObject *> m_childs;//implementer
		std::string m_nom;
		bool m_flipY = false;
		bool m_inversePos = false;
		Transform m_transform{};
		std::vector<Component *> m_component;
	};
}

#endif //__ENGINE_GRAPHIC_OBJECT__