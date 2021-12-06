#ifndef __ENGINE_SCENE_GENERATION__
#define __ENGINE_SCENE_GENERATION__

#include "GameEngine.hpp"
#include "GuiInfo.hpp"

class Generation : public Scene
{
public:
	void load();
	void unload();
private:
	GuiInfo m_gui;
};

#endif//__ENGINE_SCENE_GENERATION__