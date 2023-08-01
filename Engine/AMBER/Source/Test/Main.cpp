
#include <iostream>
#include "GameEngine.hpp"
#include "BaseScene.hpp"
using namespace Ge;

int main()
{
	Debug::Info("Moteur Graphique");	
	GameEngine engine;	
	ptrClass e = engine.getPtrClass();	
	e.settingManager->setName("Engine");
	e.settingManager->setClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	e.settingManager->setWindowHeight(1024);
	e.settingManager->setWindowWidth(1920);

	BaseScene bs;
	e.sceneManager->addScene("BaseScene",&bs);

	if (!engine.initialize())
	{
		Debug::Error("Erreur d'intialisation du moteur graphique");
		return -1;
	}		

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

