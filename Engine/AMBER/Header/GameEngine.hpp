#ifndef __ENGINE_GAME_ENGINE___
#define __ENGINE_GAME_ENGINE___

#include "Initializer.hpp"
#include "PointeurClass.hpp"
#include "Debug.hpp"
#include "RenderingEngine.hpp"
#include "SettingManager.hpp"

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
        RenderingEngine m_renderingEngine;
        Debug m_debug;
        SettingManager m_settingManager;
        ptrClass m_pointeurClass;
        VulkanMisc * m_VulkanMisc;
    };
}

#endif //__ENGINE_GAME_ENGINE___