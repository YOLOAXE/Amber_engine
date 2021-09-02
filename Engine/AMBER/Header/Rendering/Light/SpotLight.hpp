#ifndef __ENGINE_SPOT_LIGHT__
#define __ENGINE_SPOT_LIGHT__

#include "Lights.hpp"

namespace Ge
{
	class SpotLight : public Lights
	{
	public:
		SpotLight(int index, VulkanMisc * vM);
		float getConstant();
		void setConstant(float constant);
		float getLinear();
		void setLinear(float linear);
		float getQuadratic();
		void setQuadratic(float quadratic);
		float getCutOff();
		void setCutOff(float cutOff);
		float getOuterCutOff();
		void setOuterCutOff(float outerCutOff);
	};
}

#endif //__ENGINE_SPOT_LIGHT__