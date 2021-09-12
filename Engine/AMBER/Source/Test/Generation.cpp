#include "Generation.hpp"

void Generation::load()
{
	GraphiquePipeline * utimeTestPipeline = GameEngine::getPtrClass().graphiquePipelineManager->createPipeline("../Shader/shaderUTimeTest.spv", "../Shader/vert.spv");
	ShapeBuffer * sb = GameEngine::getPtrClass().modelManager->allocateBuffer("../Model/cube.obj");
	Model * m = GameEngine::getPtrClass().modelManager->createModel(sb);
	Model * m2 = GameEngine::getPtrClass().modelManager->createModel(sb);
	m->setPosition(glm::vec3(10,0,0));
	m2->setPosition(glm::vec3(0, 1, 0));
	m2->setScale(glm::vec3(1));
	Materials * mat = GameEngine::getPtrClass().materialManager->createMaterial();
	Materials * matUtime = GameEngine::getPtrClass().materialManager->createMaterial();	
	matUtime->setPipeline(utimeTestPipeline);
	m2->setMaterial(matUtime);
	mat->setAlbedoTexture(GameEngine::getPtrClass().textureManager->createTexture("../Texture/m2m2.jpg"));
	m->setMaterial(mat);	
	GameEngine::getPtrClass().lightManager->createPointLight(glm::vec3(0, 4, 0), glm::vec3(1));
	GameEngine::getPtrClass().behaviourManager->addBehaviour(&m_gui);
	GameEngine::getPtrClass().skyboxManager->loadSkybox(GameEngine::getPtrClass().textureManager->createTextureCubeMap("../Texture/skybox.png"));
	Debug::Log("Load scene");
}

void Generation::unload()
{
	GameEngine::getPtrClass().behaviourManager->removeBehaviour(&m_gui);
	Debug::Log("unload scene");
}