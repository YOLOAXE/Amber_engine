#ifndef __ENGINE_INTERFACE_SPOT_LIGHT__
#define __ENGINE_INTERFACE_SPOT_LIGHT__

#include "Light.hpp"

class SpotLight : virtual public Light
{
public:
	virtual float getConstant() = 0;
	virtual void setConstant(float constant) = 0;
	virtual float getLinear() = 0;
	virtual void setLinear(float linear) = 0;
	virtual float getQuadratic() = 0;
	virtual void setQuadratic(float quadratic) = 0;
	virtual float getCutOff() = 0;
	virtual void setCutOff(float cutOff) = 0;
	virtual float getOuterCutOff() = 0;
	virtual void setOuterCutOff(float outerCutOff) = 0;
};

#endif //__ENGINE_INTERFACE_SPOT_LIGHT__