#include "GuiInfo.hpp"

void GuiInfo::start()
{
	gammaValue = GameEngine::getPtrClass().settingManager->getGamma();
	rm = new NetworkManager();
	rm->addObject([]() { return static_cast<MirrorComponent*>(new Player()); });
}

void GuiInfo::fixedUpdate()
{

}

void GuiInfo::update()
{

	if (GameEngine::getPtrClass().inputManager->getKeyDown(GLFW_KEY_H))
	{			
		rm->initialize(true);
	}
	if (GameEngine::getPtrClass().inputManager->getKeyDown(GLFW_KEY_C))
	{						
		rm->initialize(false);
	}
}

void GuiInfo::stop()
{
	delete(rm);
}

void GuiInfo::onGUI()
{
	if (ImGui::SliderFloat("Gamma", &gammaValue, 0.0f, 10.0f))
	{
		GameEngine::getPtrClass().settingManager->setGamma(gammaValue);
	}
}