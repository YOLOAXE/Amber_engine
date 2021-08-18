#ifndef __ENGINE_INTERFACE_CAMERA__
#define __ENGINE_INTERFACE_CAMERA__

#include "Vector3.hpp"
#include "GraphicsObject.hpp"

class I_Camera : public virtual GraphicsObject
{
public:
	virtual void setFieldOfView(float fov) = 0;
	virtual void setNear(float near) = 0;
	virtual void setFar(float far) = 0;
	virtual void setPriority(int p) = 0;
	virtual void setOrtho(bool state) = 0;
	virtual float getFieldOfView() = 0;
	virtual float getNear() = 0;
	virtual float getFar() = 0;
	virtual int getPriority() = 0;
};

#endif//__ENGINE_INTERFACE_CAMERA__