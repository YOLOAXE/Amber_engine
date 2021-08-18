#ifndef __ENGINE_DIRECTIONAL_LIGHT__
#define __ENGINE_DIRECTIONAL_LIGHT__

#include "Lights.hpp"
#include "DirectionalLight.hpp"

namespace Ge
{
	class LDirectional : public Lights, public DirectionalLight
	{
	public:
		LDirectional(int index, VulkanMisc * vM);

	};
}

#endif //__ENGINE_DIRECTIONAL_LIGHT__