#include "Generation.hpp"

void Generation::load()
{
	ShapeBuffer * sb = GameEngine::getPtrClass().modelManager->allocateBuffer("../Model/cube.obj");
	ShapeBuffer * sbmansion = GameEngine::getPtrClass().modelManager->allocateBuffer("../Model/lpm.obj");
	Model * m = GameEngine::getPtrClass().modelManager->createModel(sb);
	Model * m2 = GameEngine::getPtrClass().modelManager->createModel(sb);
	Model * modelMansion = GameEngine::getPtrClass().modelManager->createModel(sbmansion);
	m->setPosition(glm::vec3(10,0,0));
	m2->setPosition(glm::vec3(0, 1, 0));
	m2->setScale(glm::vec3(1));
	Materials * mat = GameEngine::getPtrClass().materialManager->createMaterial();
	Materials * matMansion = GameEngine::getPtrClass().materialManager->createMaterial();
	Materials * matUtime = GameEngine::getPtrClass().materialManager->createMaterial();	
	m2->setMaterial(matUtime);
	matMansion->setAlbedoTexture(GameEngine::getPtrClass().textureManager->createTexture("../Texture/p.png"));
	modelMansion->setMaterial(matMansion);
	mat->setAlbedoTexture(GameEngine::getPtrClass().textureManager->createTexture("../Texture/m2m2.jpg"));	
	m->setMaterial(mat);	
	m2->addComponent(&m_gui);
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