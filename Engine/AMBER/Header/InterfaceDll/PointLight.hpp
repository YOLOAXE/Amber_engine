#ifndef __ENGINE_INTERFACE_POINT_LIGHT__
#define __ENGINE_INTERFACE_POINT_LIGHT__

#include "Light.hpp"

class PointLight : virtual public Light
{
public:
	virtual float getConstant() = 0;
	virtual void setConstant(float constant) = 0;
	virtual float getLinear() = 0;
	virtual void setLinear(float linear) = 0;
	virtual float getQuadratic() = 0;
	virtual void setQuadratic(float quadratic) = 0;
};

#endif //__ENGINE_INTERFACE_POINT_LIGHT__