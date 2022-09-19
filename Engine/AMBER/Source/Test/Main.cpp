
#include <iostream>
#include "GameEngine.hpp"
#include "WorldGeneration.hpp"

using namespace Ge;
using namespace lia;

int main()
{
	Debug::Info("Moteur Graphique");	
	GameEngine engine;	
	WorldGeneration worldGeneration;
	engine.getPtrClass().settingManager->setName("LIA");
	if (!engine.initialize())
	{
		Debug::Error("Erreur d'intialisation du moteur graphique");
		return -1;
	}		
	engine.getPtrClass().sceneManager->addScene("WorldGeneration",&worldGeneration);		
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

