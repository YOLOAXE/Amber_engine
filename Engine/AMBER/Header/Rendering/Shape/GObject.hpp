#ifndef __ENGINE_GRAPHIC_OBJECT__
#define __ENGINE_GRAPHIC_OBJECT__

#include "Transform.hpp"
#include "GraphicsObject.hpp"
#include "Debug.hpp"
#include "Component.hpp"
#include "TransformImgui.hpp"
#include "imgui-cmake/Header/imgui.h"
#include <vector>
#include <string> 

namespace Ge
{
	class GObject : virtual public GraphicsObject
	{
	public:
		GObject(bool inverse = false);
		void setName(std::string nom);
		std::string * getName();
		virtual void setPosition(Vector3 pos);
		virtual void setRotation(Vector4 rot);
		virtual void setEulerAngles(Vector3 eul);
		virtual void setScale(Vector3 scale);
		virtual void setTarget(Vector3 target);
		virtual Vector3 getPosition();
		virtual Vector4 getRotation();
		virtual Vector3 getEulerAngles();
		virtual Vector3 getScale();
		virtual void mapMemory();
		Vector3 transformDirectionAxeX();
		Vector3 transformDirectionAxeY();
		Vector3 transformDirectionAxeZ();
		Vector3 transformDirectionAxe(Vector3 dir);
		bool getFlipY();
		void setFlipY(bool state);
		void addComponent(Component * c);
		void removeComponent(Component * c);
		virtual void onGUI();
	protected:
		std::string m_nom;
		bool m_flipY = false;
		bool m_inversePos = true;
		Transform m_transform{};
		TransformImgui m_transformImgui{};
		std::vector<Component *> m_Component;
	};
}

#endif //__ENGINE_GRAPHIC_OBJECT__