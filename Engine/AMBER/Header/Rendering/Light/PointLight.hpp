#ifndef __ENGINE_POINT_LIGHT__
#define __ENGINE_POINT_LIGHT__

#include "Lights.hpp"

namespace Ge
{
	class PointLight : public Lights
	{
	public:
		PointLight(int index, VulkanMisc * vM);
		float getConstant();
		void setConstant(float constant);
		float getLinear();
		void setLinear(float linear);
		float getQuadratic();
		void setQuadratic(float quadratic);
	};
}

#endif //__ENGINE_POINT_LIGHT__