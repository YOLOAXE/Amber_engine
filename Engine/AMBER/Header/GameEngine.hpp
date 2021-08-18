#ifndef __ENGINE_GAME_ENGINE___
#define __ENGINE_GAME_ENGINE___

#include "Initializer.hpp"
#include "PointeurClass.hpp"
#include "Debug.hpp"
#include "RenderingEngine.hpp"
#include "SettingManager.hpp"
#include "Time.hpp"
#include "InputManager.hpp"

namespace Ge
{
    class GameEngine : Initializer
    {
    public:
        bool initialize();
        void release();
        void start();
        void update();

    private:
        VulkanMisc * m_VulkanMisc;
        RenderingEngine m_renderingEngine;
        Debug m_debug;
        SettingManager m_settingManager;
        ptrClass m_pointeurClass; 
        Time m_time;
        InputManager m_inputManager;
        float m_lag = 0.0f;
    };
}

#endif //__ENGINE_GAME_ENGINE___