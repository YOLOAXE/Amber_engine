#ifndef __ENGINE_INTERFACE_SETTING_MANAGER__
#define __ENGINE_INTERFACE_SETTING_MANAGER__

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Version.hpp"

class I_SettingManager
{
public:
	virtual double getFps() = 0;
	virtual void setFps(double fps) = 0;
	virtual const char *getName() = 0;
	virtual void setName(const char *name) = 0;
	virtual double getWindowHeight() = 0;
	virtual void setWindowHeight(double height) = 0;
	virtual double getWindowWidth() = 0;
	virtual void setWindowWidth(double Width) = 0;
	virtual Vector3 getGravity() = 0;
	virtual void setGravity(Vector3 gravity) = 0;
	virtual void setVersion(Version v) = 0;
	virtual Version getVersion() = 0;
	virtual void setClearColor(Vector4 color) = 0;
	virtual Vector4 getClearColor() = 0;
	virtual void setGamma(float gamma) = 0;
	virtual float getGamma() = 0;
};

#endif //__ENGINE_INTERFACE_SETTING_MANAGER__