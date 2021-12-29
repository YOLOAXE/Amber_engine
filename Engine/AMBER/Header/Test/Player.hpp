#ifndef __ENGINE_PLAYER_INFO__
#define __ENGINE_PLAYER_INFO__

#include "Behaviour.hpp"
#include "GameEngine.hpp"
#include "MirrorComponent.hpp"
#include "NetValue.hpp"

class Player : public MirrorComponent
{
public:
	void mirrorStart();
	void mirrorFixedUpdate();
	void mirrorUpdate();
	void mirrorStop();
	void onGUI();
private:
	ShapeBuffer * sb;
	Model * m;
	/*NetValue<float> posX;
	NetValue<float> posY;
	NetValue<float> posZ;*/
};

#endif//__ENGINE_PLAYER_INFO__