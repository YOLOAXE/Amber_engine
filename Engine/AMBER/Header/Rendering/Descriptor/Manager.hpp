#ifndef __ENGINE_MANAGER__
#define __ENGINE_MANAGER__

#include "VulkanMisc.hpp"
#include "Descriptor.hpp"

namespace Ge
{
	class Manager
	{
	public:
		virtual void initDescriptor(VulkanMisc * vM) = 0;
		virtual void updateDescriptor() = 0;
		Descriptor* getDescriptor();
	protected:
		Descriptor *m_descriptor = nullptr;
	};
}

#endif//__ENGINE_MANAGER__