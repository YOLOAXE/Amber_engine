#ifndef __ENGINE_SHADER_UNIFORM_BUFFER_DIVERS__
#define __ENGINE_SHADER_UNIFORM_BUFFER_DIVERS__

#include "Debug.hpp"
#include "VulkanMisc.hpp"
#include "UniformBufferDiver.hpp"
#include "BufferManager.hpp"
#include "Descriptor.hpp"

namespace Ge
{
    class ShaderUniformBufferDivers
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();        
        void updateUniformBufferDiver();
        static VkDescriptorSetLayout createVkDescriptorSetLayout(VulkanMisc *vM);
        static VkDescriptorPool createVkDescriptorPool(VulkanMisc *vM);

    private:
        VulkanMisc *vulkanM;
        UniformBufferDiver m_ubd;
        VmaBuffer m_vmaUniformBuffer;

    public:
        static Descriptor * m_descriptor;
    };
}

#endif //__ENGINE_SHADER_UNIFORM_BUFFER_DIVERS__