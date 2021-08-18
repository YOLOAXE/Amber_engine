#ifndef __ENGINE_POINTEUR_CLASS__
#define __ENGINE_POINTEUR_CLASS__

#include "I_Debug.hpp"
#include "I_SettingManager.hpp"
#include "I_InputManager.hpp"

struct ptrClass
{
    I_Debug * pi_debug;
    I_SettingManager * pi_settingManager;
    I_InputManager * pi_inputManager;
};

#endif //__ENGINE_POINTEUR_CLASS__