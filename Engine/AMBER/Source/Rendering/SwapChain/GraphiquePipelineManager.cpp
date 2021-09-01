
#include "GraphiquePipelineManager.hpp"

namespace Ge
{
	std::map<Pipeline *, GraphiquePipeline * > GraphiquePipelineManager::m_GraphiquePipeline;
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
		for (std::map<Pipeline *, GraphiquePipeline *>::iterator iter = m_GraphiquePipeline.begin(); iter != m_GraphiquePipeline.end(); ++iter)
		{
			delete (iter->second);
		}
		m_GraphiquePipeline.clear();
	}

	Pipeline * GraphiquePipelineManager::createPipeline(const std::string &frag, const std::string &vert)
	{
		GraphiquePipeline * gp = new GraphiquePipeline(vulkanM, frag, vert);
		Pipeline * p = (Pipeline *)gp;
		m_GraphiquePipeline[p] = gp;
		ShaderPair * sp = new ShaderPair(frag, vert);
		m_fileNameShaders.push_back(sp);
		return p;
	}

	std::map<Pipeline *, GraphiquePipeline * > GraphiquePipelineManager::GetPipeline()
	{
		return m_GraphiquePipeline;
	}

	void GraphiquePipelineManager::destroyPipeline(Pipeline * pipeline)
	{
		GraphiquePipeline * gp = m_GraphiquePipeline[pipeline];
		m_GraphiquePipeline.erase(pipeline);
		delete (gp);
	}
}