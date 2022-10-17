
#include <iostream>
#include "GameEngine.hpp"

using namespace Ge;

int main()
{
	Debug::Info("Moteur Graphique");	
	GameEngine engine;	
	engine.getPtrClass().settingManager->setName("LIA");
	if (!engine.initialize())
	{
		Debug::Error("Erreur d'intialisation du moteur graphique");
		return -1;
	}		

	ShapeBuffer * sb = engine.getPtrClass().modelManager->allocateBuffer("../Model/cube.obj");
	Model * m = engine.getPtrClass().modelManager->createModel(sb,"Test");
	m->setScale(glm::vec3(20,20,20));
	m->setPosition(glm::vec3(0, -20, 0));
	Lights * l = engine.getPtrClass().lightManager->createPointLight(glm::vec3(0, 5, 0), glm::vec3(1, 1, 1));
	Materials* mat = engine.getPtrClass().materialManager->createMaterial();
	Textures* albedo = engine.getPtrClass().textureManager->createTexture("../Texture/pbrAlbedo.png");
	Textures* metallic = engine.getPtrClass().textureManager->createTexture("../Texture/pbrMetallic.png");
	Textures* normal = engine.getPtrClass().textureManager->createTexture("../Texture/pbrNormal.png");
	mat->setAlbedoTexture(albedo);
	mat->setNormalTexture(normal);
	mat->setMetallicTexture(metallic);
	mat->setMetallic(0.7f);
	mat->setRoughness(0.1f);	
	mat->setOffset(glm::vec2(10, 10));
	m->setMaterial(mat);
	try
	{
		engine.start();
	}
	catch (std::runtime_error& e)
	{
		Debug::Error("Exception : %s", e.what());
		return -1;
	}
	catch (std::bad_alloc& e)
	{
		Debug::Error("Exception : %s", e.what());
		return -1;
	}
	catch (const std::exception& e)
	{
		Debug::Error("Exception : %s", e.what());
		return -1;
	}
	engine.release();
	std::cin.ignore();
	return 0;
}

