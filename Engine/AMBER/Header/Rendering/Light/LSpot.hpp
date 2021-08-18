#ifndef __ENGINE_SPOT_LIGHT__
#define __ENGINE_SPOT_LIGHT__

#include "SpotLight.hpp"
#include "Lights.hpp"

namespace Ge
{
	class LSpot : public Lights, public SpotLight
	{
	public:
		LSpot(int index, VulkanMisc * vM);
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