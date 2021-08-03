#ifndef __ENGINE_GRAPHIQUE_PIPELINE__
#define __ENGINE_GRAPHIQUE_PIPELINE__

#include "vulkan/vulkan.h"
#include "Debug.hpp"
#include <fstream>
#include <array>
#include "VulkanMisc.hpp"
#include "ShaderElement.hpp"
#include "VertexVulkan.hpp"
#include <algorithm>
#include "PushConstants.hpp"

namespace Ge
{
    class GraphiquePipeline
    {
    public:
        GraphiquePipeline(VulkanMisc *vM, std::string FragFile, std::string VertFile);
        ~GraphiquePipeline();

    private:
        static ShaderElement LoadShader(const std::string &filename, const char *entry, VkDevice device, bool isVertex);
        static void DestroyShaderElement(VkDevice device, ShaderElement se);
        static std::vector<char> readFile(const std::string &filename);
        static VkShaderModule createShaderModule(const std::vector<char> &code, VkDevice device);
    public:
        GraphiquePipelineElement m_graphiquePipelineElement;
    private:
        VulkanMisc *vulkanM;
    };
}

#endif //__ENGINE_GRAPHIQUE_PIPELINE__