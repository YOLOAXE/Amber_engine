#ifndef __ENGINE_DESCRIPTOR__
#define __ENGINE_DESCRIPTOR__

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include <algorithm>

namespace Ge
{
    class Descriptor
    {
    public:
        Descriptor(VulkanMisc *vM, VkDescriptorType descriptorType, int baseCount);
		~Descriptor();
        VkDescriptorSetLayout getDescriptorSetLayout();
        VkDescriptorPool getDescriptorPool();
        std::vector<VkDescriptorSet> getDescriptorSets();
        void updateCount(VulkanMisc *vM, int count, std::vector<VkDescriptorBufferInfo> bufferInfo);
        void updateCount(VulkanMisc *vM, int count, std::vector<VkDescriptorImageInfo> bufferInfo);
    private:
        static VkDescriptorPool createVkDescriptorPool(VulkanMisc *vM, int count, VkDescriptorType type);
        static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM, int count, VkDescriptorType type, int descriptorCount);
        static std::vector<VkDescriptorSet> createVkDescriptorSet(VulkanMisc *vM, VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool descriptorPool);
        static void destroyVkDescriptorSet(VulkanMisc *vM, std::vector<VkDescriptorSet> descriptorSets, VkDescriptorPool descriptorPool);
        static void destroyVkDescriptorPool(VulkanMisc *vM, VkDescriptorPool descriptorPool);
        static void destroyVkVkDescriptorSetLayout(VulkanMisc *vM, VkDescriptorSetLayout descriptorSetLayout);

    private:
		static int countDescriptor;
        VulkanMisc *vulkanM;
        VkDescriptorSetLayout m_DescriptorSetLayout;
        VkDescriptorPool m_DescriptorPool;
        std::vector<VkDescriptorSet> m_DescriptorSets;
        VkDescriptorType m_descriptorType;
        int m_count = 0;
        int m_sizeOfResource = 0;
		int m_countDescriptor = 0;
    };
}

#endif //__ENGINE_DESCRIPTOR__