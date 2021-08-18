#ifndef __ENGINE_INTERFACE_LIGHT__
#define __ENGINE_INTERFACE_LIGHT__

#include "Vector3.hpp"
#include "GraphicsObject.hpp"

class Light: public virtual GraphicsObject
{
public:
	virtual void setColors(Vector3 color) = 0;
	virtual Vector3 getColors() = 0;
	virtual void setSpecular(Vector3 spec) = 0;
	virtual Vector3 getSpecular() = 0;
	virtual void setAmbiant(Vector3 ambiant) = 0;
	virtual Vector3 getAmbiant() = 0;
	virtual void setShadow(bool state) = 0;
	virtual bool getShadow() = 0;
};

#endif //__ENGINE_INTERFACE_LIGHT__
