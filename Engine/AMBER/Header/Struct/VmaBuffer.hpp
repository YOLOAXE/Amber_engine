#ifndef __ENGINE_VMA_BUFFER__
#define __ENGINE_VMA_BUFFER__

#include "vk_mem_alloc.h"

struct VmaBuffer
{
    VkBuffer buffer;
    VmaAllocation allocation;
};

#endif //__ENGINE_VMA_BUFFER__