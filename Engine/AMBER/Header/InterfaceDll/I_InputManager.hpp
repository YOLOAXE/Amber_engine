#ifndef __ENGINE_INTERFACE_INPUT_MANAGER__
#define __ENGINE_INTERFACE_INPUT_MANAGER__

class I_InputManager
{
public:
	virtual bool getKey(int key) = 0;
	virtual bool getKeyUp(int key) = 0;
	virtual bool getKeyDown(int key) = 0;
	virtual bool getMouse(int key) = 0;
	virtual double axisMouseX() = 0;
	virtual double axisMouseY() = 0;
	virtual double getMousePosX() = 0;
	virtual double getMousePosY() = 0;
	virtual const char * getGamepadName(int jid) = 0;
	virtual bool getGamepadState(int jid, int key) = 0;
	virtual float getGamepadAxis(int jid, int indice) = 0;
};


#endif //__ENGINE_INTERFACE_INPUT_MANAGER__