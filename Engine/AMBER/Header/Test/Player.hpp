#ifndef __ENGINE_PLAYER_INFO__
#define __ENGINE_PLAYER_INFO__

#include "Behaviour.hpp"
#include "GameEngine.hpp"
#include "MirrorComponent.hpp"

class Player : public MirrorComponent
{
public:
	void start();
	void fixedUpdate();
	void update();
	void stop();
	void onGUI();
private:
	ShapeBuffer * sb;
	Model * m;
};

#endif//__ENGINE_PLAYER_INFO__