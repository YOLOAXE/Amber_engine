
#include "GraphiquePipelineManager.hpp"

namespace Ge
{
	std::vector<GraphiquePipeline *> GraphiquePipelineManager::m_graphiquePipeline;
	bool GraphiquePipelineManager::initialize(VulkanMisc *vM)
	{
		vulkanM = vM;
		for (int i = 0; i < m_fileNameShaders.size(); i++)
		{
			createPipeline(m_fileNameShaders[i]->Frag, m_fileNameShaders[i]->Vert);
		}
		if (m_fileNameShaders.size() == 0)
		{
			createPipeline("../Shader/frag.spv", "../Shader/vert.spv");			
		}
		return true;
	}

	void GraphiquePipelineManager::release()
	{
		for (int i = 0; i < m_graphiquePipeline.size();i++)
		{
			delete (m_graphiquePipeline[i]);
		}
		m_graphiquePipeline.clear();
	}

	GraphiquePipeline * GraphiquePipelineManager::createPipeline(const std::string &frag, const std::string &vert)
	{
		ShaderPair * sp = new ShaderPair(frag, vert);
		GraphiquePipeline * gp = new GraphiquePipeline(vulkanM, frag, vert);
		m_graphiquePipeline.push_back(gp);		
		m_fileNameShaders.push_back(sp);
		return gp;
	}

	std::vector<GraphiquePipeline *> GraphiquePipelineManager::GetPipelines()
	{
		return m_graphiquePipeline;
	}

	void GraphiquePipelineManager::destroyPipeline(GraphiquePipeline * pipeline)
	{
		m_graphiquePipeline.erase(std::remove(m_graphiquePipeline.begin(), m_graphiquePipeline.end(), pipeline), m_graphiquePipeline.end());
		//TODO suprimer les shader pair
		delete (pipeline);
	}
}