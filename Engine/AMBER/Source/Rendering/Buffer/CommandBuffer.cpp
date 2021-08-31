#include "CommandBuffer.hpp"

namespace Ge
{

	bool CommandBuffer::initialize(VulkanMisc * vM)
	{
		vulkanM = vM;
		return true;
	}

	void CommandBuffer::release()
	{

	}

}