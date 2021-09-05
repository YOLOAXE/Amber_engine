#include "Generation.hpp"

void Generation::load()
{
	ShapeBuffer * sb = GameEngine::getPtrClass().modelManager->allocateBuffer("../Model/cube.obj");
	Model * m = GameEngine::getPtrClass().modelManager->createModel(sb);
	Materials * mat = GameEngine::getPtrClass().materialManager->createMaterial();
	mat->setAlbedoTexture(GameEngine::getPtrClass().textureManager->createTexture("../Texture/m2m2.jpg"));
	m->setMaterial(mat);	
	GameEngine::getPtrClass().behaviourManager->addBehaviour(&m_gui);
	Debug::Log("Load scene");
}

void Generation::unload()
{
	GameEngine::getPtrClass().behaviourManager->removeBehaviour(&m_gui);
	Debug::Log("unload scene");
}