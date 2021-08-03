#ifndef __ENGINE_GRAPHIQUE_PIPELINE_MANAGER__
#define __ENGINE_GRAPHIQUE_PIPELINE_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include <vector>
#include "GraphiquePipeline.hpp"

namespace Ge
{
    class GraphiquePipelineManager
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();
        void/*pipeline*/ createPipeline(const std::string & frag,const std::string & vert);
        void destroyPipeline(/*pipeline*/);
    private:
        VulkanMisc *vulkanM;
        std::vector<std::string> m_fileNameFragShaders; 
        std::vector<std::string> m_fileNameVertShaders;
        std::vector<GraphiquePipeline *> m_allPipelines;
    };
}

#endif //__ENGINE_GRAPHIQUE_PIPELINE_MANAGER__