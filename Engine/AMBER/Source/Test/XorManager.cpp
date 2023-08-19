#include "XorManager.hpp"

template <class T>
void DebugArray(T* arrayData, int size, int separator)
{
	std::string listarray = "";
	for (int i = 0; i < size; i++)
	{
		if (i % separator == 0 && i != 0)
		{
			listarray += "\n\n";
		}
		listarray += std::to_string(arrayData[i]) + ",";
	}
	std::cout << listarray << std::endl << std::endl;
}

void XorManager::start()
{
	m_pc = GameEngine::getPtrClass();
	m_nnd.nb_input_layer = 2;
	m_nnd.nb_output_layer = 1;
	m_nnd.nb_col_hiden_layer = 3;
	m_nnd.nb_hiden_layer = 20;
	m_nnd.mutation_multiplayer = 0.1f;
	m_nnd.mutation_rate = 0.08f;	
	m_nnd.select_sub_best_neural = 1;
	srand(time(NULL));
	m_nld.seed = rand();
	Debug::Log("Seed : %d", m_nld.seed);

	m_nnd.activationSize = m_nnd.nb_input_layer + m_nnd.nb_col_hiden_layer * m_nnd.nb_hiden_layer + m_nnd.nb_output_layer;
	m_nnd.weightSize = m_nnd.nb_input_layer * m_nnd.nb_hiden_layer;
	for (int i = 0; i < m_nnd.nb_col_hiden_layer - 1; i++)
	{
		m_nnd.weightSize += m_nnd.nb_hiden_layer * m_nnd.nb_hiden_layer;
	}
	m_nnd.weightSize += m_nnd.nb_hiden_layer * m_nnd.nb_output_layer;
	int layerStep = 2 + m_nnd.nb_col_hiden_layer;
	nb_neural_network = 70000;// 70000;
	m_nld.size = nb_neural_network* m_nnd.weightSize;
	Debug::Log("Neural info \n nb_neural_network : %d \n activationSize : %d \n weightSize : %d \n nb_neural_network * weightSize : %d \n size mo : %f", nb_neural_network, m_nnd.activationSize, m_nnd.weightSize, nb_neural_network * m_nnd.weightSize, (float)(nb_neural_network * m_nnd.weightSize * 4.0f) / 1000000.0f);
	weightBuffer = m_pc.computeShaderManager->createComputeBuffer(nb_neural_network * m_nnd.weightSize, sizeof(float));
	activationBuffer = m_pc.computeShaderManager->createComputeBuffer(nb_neural_network * m_nnd.activationSize, sizeof(float));
	scoreBuffer = m_pc.computeShaderManager->createComputeBuffer(nb_neural_network, sizeof(float));
	scoreIndexBuffer = m_pc.computeShaderManager->createComputeBuffer(nb_neural_network, sizeof(int));
	scoreIndexSubBuffer = m_pc.computeShaderManager->createComputeBuffer(nb_neural_network, sizeof(int));
	nndBuffer = m_pc.computeShaderManager->createComputeBuffer(1, sizeof(NeuralNetworkData));
	nldBuffer = m_pc.computeShaderManager->createComputeBuffer(1, sizeof(NeuralSwapData));
	sBuffer = m_pc.computeShaderManager->createComputeBuffer(1, sizeof(ScoreData));
	bestWeight = m_pc.computeShaderManager->createComputeBuffer(max_best_neural * m_nnd.weightSize, sizeof(float));
	nndBuffer->SetData((void*)(&m_nnd), 0, 0, 1);
	nldBuffer->SetData((void*)(&m_nld), 0, 0, 1);

	std::vector<ComputeData*> cdiw;
	cdiw.push_back(nndBuffer);
	cdiw.push_back(nldBuffer);
	cdiw.push_back(weightBuffer);
	m_initWeight = m_pc.computeShaderManager->createComputeShader("../Shader/nn/init_weight.comp.spv", cdiw);	

	std::vector<ComputeData*> cdnn;
	cdnn.push_back(nndBuffer);
	cdnn.push_back(nldBuffer);
	cdnn.push_back(weightBuffer);
	cdnn.push_back(activationBuffer);
	m_neuralNetwork = m_pc.computeShaderManager->createComputeShader("../Shader/nn/neural_network.comp.spv", cdnn);

	std::vector<ComputeData*> cds;
	cds.push_back(nndBuffer);
	cds.push_back(nldBuffer);
	cds.push_back(scoreBuffer);
	m_resetScore = m_pc.computeShaderManager->createComputeShader("../Shader/nn/reset_score.comp.spv", cds);

	std::vector<ComputeData*> cdix;
	cdix.push_back(nndBuffer);
	cdix.push_back(nldBuffer);
	cdix.push_back(activationBuffer);
	m_initXor = m_pc.computeShaderManager->createComputeShader("../Shader/nn/init_xor.comp.spv", cdix);

	std::vector<ComputeData*> cdxs;
	cdxs.push_back(nndBuffer);
	cdxs.push_back(nldBuffer);
	cdxs.push_back(activationBuffer);
	cdxs.push_back(scoreBuffer);
	m_xorScore = m_pc.computeShaderManager->createComputeShader("../Shader/nn/score_xor.comp.spv", cdxs);

	std::vector<ComputeData*> cdbs;
	cdbs.push_back(nldBuffer);
	cdbs.push_back(scoreBuffer);
	cdbs.push_back(scoreIndexBuffer);
	cdbs.push_back(scoreIndexSubBuffer);
	cdbs.push_back(sBuffer);
	m_bestScore = m_pc.computeShaderManager->createComputeShader("../Shader/nn/best_score.comp.spv", cdbs);

	std::vector<ComputeData*> cdbnn;
	cdbnn.push_back(nndBuffer);
	cdbnn.push_back(nldBuffer);
	cdbnn.push_back(bestWeight);
	cdbnn.push_back(weightBuffer);
	cdbnn.push_back(scoreIndexSubBuffer);
	m_cmpBest = m_pc.computeShaderManager->createComputeShader("../Shader/nn/cmp_best.comp.spv", cdbnn);

	std::vector<ComputeData*> cdunn;
	cdunn.push_back(nndBuffer);
	cdunn.push_back(nldBuffer);
	cdunn.push_back(bestWeight);
	cdunn.push_back(weightBuffer);
	m_updateNeuralNetwork = m_pc.computeShaderManager->createComputeShader("../Shader/nn/update_nn.comp.spv", cdunn);	

	std::vector<int> decomposition = ShaderUtil::DecomposeFirstFactors(nb_neural_network);
	sort(decomposition.begin(), decomposition.end());
	std::string decomposeLog = "";
	for (int i = 0; i < decomposition.size(); i++)
	{
		decomposeLog += std::to_string(decomposition[i]) + ",";
	}
	Debug::Log("decomposition %s", decomposeLog.c_str());
	if (decomposition.size() <= 1)
	{
		Debug::Error("Fail to decompose : %d", nb_neural_network);
		return;
	}
	int x, y, z;
	int xs, ys, zs;
	ShaderUtil::CalcWorkSize(nb_neural_network, &xs, &ys, &zs);
	ShaderUtil::CalcWorkSize(m_nld.size, &x, &y, &z);
	m_initWeight->dispatch(x, y, z);	
	int* indexBestScore = new int[1];
	float* bestscore = new float[1];
	m_nnd.select_sub_best_neural = clamp(decomposition[1],1, max_best_neural);

	int nrd = rand();
	for (int ml = 0; ml < mutation_gen_loop; ml++)
	{		
		m_nld.size = nb_neural_network;
		m_nld.seed = nrd;
		nldBuffer->SetData((void*)(&m_nld), 0, 0, 1);
		m_resetScore->dispatch(xs, ys, zs);

		for (int nx = 0; nx < 15; nx++)
		{
			m_nld.size = nb_neural_network * m_nnd.activationSize;
			m_nld.seed++;
			ShaderUtil::CalcWorkSize(m_nld.size, &x, &y, &z);			
			nldBuffer->SetData((void*)(&m_nld), 0, 0, 1);	
			m_initXor->dispatch(x, y, z);

			m_nld.size = nb_neural_network * m_nnd.weightSize;
			ShaderUtil::CalcWorkSize(m_nld.size, &x, &y, &z);
			for (int i = 0; i < layerStep - 1; i++)
			{
				m_nld.layerId = i + 1;
				nldBuffer->SetData((void*)(&m_nld), 0, 0, 1);
				m_neuralNetwork->dispatch(x, y, z);	
			}

			m_nld.size = nb_neural_network;
			nldBuffer->SetData((void*)(&m_nld), 0, 0, 1);
			m_xorScore->dispatch(xs, ys, zs);
		}

		int decomposeValue = nb_neural_network;
		for (int i = 0; i < decomposition.size(); i++)
		{
			decomposeValue /= decomposition[i];
			ShaderUtil::CalcWorkSize(decomposeValue, &x, &y, &z);
			m_nld.size = decomposeValue;
			m_sd.initDecompose = i;
			m_sd.scorePerThread = decomposition[i];
			nldBuffer->SetData((void*)(&m_nld), 0, 0, 1);
			sBuffer->SetData((void*)(&m_sd), 0, 0, 1);
			m_bestScore->swapBuffer(2, 3);
			m_bestScore->dispatch(x, y, z);
		}
		ComputeBuffer* finalBuffer = (ComputeBuffer*)m_bestScore->getComputeData(3);
		((ComputeBuffer*)m_bestScore->getComputeData(2))->GetData((void*)indexBestScore, 0, 0, 1);
		scoreBuffer->GetData((void*)bestscore, 0, indexBestScore[0], 1);

		m_cmpBest->setComputeData(4,finalBuffer);
		
		m_nld.size = m_nnd.select_sub_best_neural * m_nnd.weightSize;
		nldBuffer->SetData((void*)(&m_nld), 0, 0, 1);
		ShaderUtil::CalcWorkSize(m_nld.size, &x, &y, &z);
		m_cmpBest->dispatch(x, y, z);

		m_nld.size = nb_neural_network * m_nnd.weightSize;
		nldBuffer->SetData((void*)(&m_nld), 0, 0, 1);
		ShaderUtil::CalcWorkSize(m_nld.size, &x, &y, &z);
		m_updateNeuralNetwork->dispatch(x, y, z);

		Debug::Log("Mutation loop : %d score : %f", ml, bestscore[0]);		
	}
	delete indexBestScore;
	delete bestscore;
	
}

void XorManager::fixedUpdate()
{

}

void XorManager::update()
{

}

void XorManager::stop()
{
	delete weightBuffer;
	delete activationBuffer;
	delete scoreBuffer;
	delete scoreIndexBuffer;
	delete scoreIndexSubBuffer;
	delete nndBuffer;
	delete nldBuffer;
	delete bestWeight;
	delete sBuffer;
	delete m_updateNeuralNetwork;
	delete m_initWeight;
	delete m_initXor;
	delete m_neuralNetwork;
	delete m_resetScore;
	delete m_xorScore;	
	delete m_bestScore;
	delete m_cmpBest;
}

void XorManager::onGUI()
{

}