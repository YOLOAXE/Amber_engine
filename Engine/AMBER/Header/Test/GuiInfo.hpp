#ifndef __ENGINE_GUI_INFO__
#define __ENGINE_GUI_INFO__

#include "Behaviour.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

class GuiInfo : public Behaviour 
{
public:
	void start();
	void fixedUpdate();
	void update();
	void stop();
	void onGUI();
private:
	float gammaValue;
	NetworkManager * rm;

};

#endif//__ENGINE_GUI_INFO__