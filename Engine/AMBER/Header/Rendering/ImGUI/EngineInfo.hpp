#ifndef __ENGINE_INFO__
#define __ENGINE_INFO__

#include "ImguiBlock.hpp"

namespace Ge
{
	class EngineInfo : public ImguiBlock
	{
	public:
		void render(VulkanMisc* vM);
	private:
		bool m_open = true;
	};

}

#endif // !__ENGINE_INFO__
