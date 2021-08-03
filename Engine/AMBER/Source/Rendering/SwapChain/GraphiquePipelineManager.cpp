#include "GraphiquePipelineManager.hpp"

namespace Ge
{
    bool GraphiquePipelineManager::initialize(VulkanMisc *vM)
    {
        vulkanM = vM;
        if(m_fileNameFragShaders.size() == 0 && m_fileNameVertShaders.size() == 0)
        {
            m_fileNameFragShaders.push_back("../Shader/frag.spv");
            m_fileNameVertShaders.push_back("../Shader/vert.spv");
        }        
        for(int i = 0 ;  i < m_fileNameFragShaders.size() ; i++)
        {
            m_allPipelines.push_back(new GraphiquePipeline(vulkanM,m_fileNameFragShaders[i],m_fileNameVertShaders[i]));
        }
        return true;
    }

    void GraphiquePipelineManager::release()
    {
        for(int i = 0; i < m_allPipelines.size(); i++)
        {
            delete(m_allPipelines[i]);
        }
        m_allPipelines.clear();   
    }

    void GraphiquePipelineManager::createPipeline(const std::string &frag, const std::string &vert)
    {
        m_fileNameFragShaders.push_back(frag);
        m_fileNameVertShaders.push_back(vert);
        m_allPipelines.push_back(new GraphiquePipeline(vulkanM,frag,vert));
    }

    void GraphiquePipelineManager::destroyPipeline()
    {
        
    }
}