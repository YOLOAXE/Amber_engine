#include "GuiInfo.hpp"

void GuiInfo::start()
{
	gammaValue = GameEngine::getPtrClass().settingManager->getGamma();
}

void GuiInfo::fixedUpdate()
{

}

void GuiInfo::update()
{
	//GameEngine::getPtrClass().cameraManager->getCurrentCamera()->setTarget(glm::vec3(0.0f));
	
}

void GuiInfo::stop()
{

}

void GuiInfo::onGUI()
{
	if (ImGui::SliderFloat("Gamma", &gammaValue, 0.0f, 10.0f))
	{
		GameEngine::getPtrClass().settingManager->setGamma(gammaValue);
	}
}