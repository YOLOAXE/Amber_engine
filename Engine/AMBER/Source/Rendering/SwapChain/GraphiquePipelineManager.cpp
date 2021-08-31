#include "GraphiquePipelineManager.hpp"

namespace Ge
{
    bool GraphiquePipelineManager::initialize(VulkanMisc *vM)
    {
        vulkanM = vM;
        for(int i = 0; i < m_fileNameShaders.size(); i++)
        {
            createPipeline(m_fileNameShaders[i]->Frag,m_fileNameShaders[i]->Vert);
        }
        if(m_fileNameShaders.size() == 0)
        {
            createPipeline("../Shader/frag.spv","../Shader/vert.spv");
        }                
        return true;
    }

    void GraphiquePipelineManager::release()
    {        
        //delete(m_allPipelines[i]);
    }

    Pipeline * GraphiquePipelineManager::createPipeline(const std::string &frag, const std::string &vert)
    {
        GraphiquePipeline * gp  = new GraphiquePipeline(vulkanM,frag,vert);
        Pipeline * p = (Pipeline *)gp;
        m_GraphiquePipeline[p] = gp;
        ShaderPair * sp =  new ShaderPair();
        m_fileNameShaders.push_back(sp);
        sp->Frag = frag;
        sp->Vert = vert;
        return p;
    }

    void GraphiquePipelineManager::destroyPipeline(Pipeline * pipeline)
    {
        
    }
}