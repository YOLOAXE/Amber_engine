#include "LDirectional.hpp"

namespace Ge
{
	LDirectional::LDirectional(int index, VulkanMisc * vM) : Lights(index, vM)
	{
		m_ubl.status = 0;
	}
}