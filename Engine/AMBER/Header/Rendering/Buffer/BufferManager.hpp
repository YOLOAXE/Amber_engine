#ifndef __ENGINE_BUFFER_MANAGER__
#define __ENGINE_BUFFER_MANAGER__

#include "vk_mem_alloc.h"
#include "Debug.hpp"
#include "Initializer.hpp"

namespace Ge
{
    struct VmaBuffer
    {
        VkBuffer buffer;
        VmaAllocation allocation;
    };
    struct VmaBufferImage
    {
        VkImage image;
        VmaAllocation allocation;
    };
    class BufferManager : Initializer
    {
    private:
        friend class RenderingEngine;
        bool initialize();
        void Release();

    public:
        BufferManager();        
        static bool createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags flags, VmaBuffer &buffer);
        static bool createImageBuffer(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VmaBufferImage &image);
        static void destroyBuffer(VmaBuffer &buffer);
        static void destroyImageBuffer(VmaBufferImage &buffer);
        static void *mapMemory(VmaBuffer &buffer);
        static void unMapMemory(VmaBuffer &buffer);
        static void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        static void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    private:
        static BufferManager *s_pInstance;
        VmaAllocator m_allocator;
    };
}

#endif //__ENGINE_BUFFER_MANAGER__