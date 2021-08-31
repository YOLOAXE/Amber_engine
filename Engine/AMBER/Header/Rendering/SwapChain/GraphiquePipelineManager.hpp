#ifndef __ENGINE_GRAPHIQUE_PIPELINE_MANAGER__
#define __ENGINE_GRAPHIQUE_PIPELINE_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include <vector>
#include "GraphiquePipeline.hpp"
#include "ShaderPair.hpp"
#include <map>

namespace Ge
{
    class GraphiquePipelineManager
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();
        Pipeline *  createPipeline(const std::string & frag,const std::string & vert);
        void destroyPipeline(Pipeline * pipeline);
    private:
        VulkanMisc *vulkanM;        
        std::vector<ShaderPair *> m_fileNameShaders;        
        std::map<Pipeline *,GraphiquePipeline * > m_GraphiquePipeline;
    };
}

#endif //__ENGINE_GRAPHIQUE_PIPELINE_MANAGER__