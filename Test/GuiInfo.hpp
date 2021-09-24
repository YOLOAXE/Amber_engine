#ifndef __ENGINE_GUI_INFO__
#define __ENGINE_GUI_INFO__

#include "Behaviour.hpp"
#include "GameEngine.hpp"

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
};

#endif//__ENGINE_GUI_INFO__