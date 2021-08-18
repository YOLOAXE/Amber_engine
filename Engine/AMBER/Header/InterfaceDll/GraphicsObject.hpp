#ifndef __ENGINE_INTERFACE_GRAPHICS_OBJECT__
#define __ENGINE_INTERFACE_GRAPHICS_OBJECT__

#include "Vector3.hpp"
#include  "Vector4.hpp"
#include <string>

class GraphicsObject
{
public:
	virtual void setPosition(Vector3 pos) = 0;
	virtual void setRotation(Vector4 rot) = 0;
	virtual void setEulerAngles(Vector3 eul) = 0;
	virtual void setScale(Vector3 pos) = 0;
	virtual void setTarget(Vector3 target) = 0;
	virtual Vector3 getPosition() = 0;
	virtual Vector4 getRotation() = 0;
	virtual Vector3 getEulerAngles() = 0;
	virtual Vector3 getScale() = 0;
	virtual void setName(std::string name) = 0;
	virtual std::string * getName() = 0;
	virtual Vector3 transformDirectionAxeX() = 0;
	virtual Vector3 transformDirectionAxeY() = 0;
	virtual Vector3 transformDirectionAxeZ() = 0;
	virtual bool getFlipY() = 0;
	virtual void setFlipY(bool state) = 0;
};

#endif // !__CAPS_INTERFACE_GRAPHICS_OBJECT__