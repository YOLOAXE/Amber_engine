#include "GameEngine.hpp"

namespace Ge
{
    bool GameEngine::initialize()
    {
        if(!m_debug.initialize())
        {
            Debug::INITFAILED("Debug");
            return false;
        }
        if(!m_settingManager.initialize())
        {
            Debug::INITFAILED("SettingManager");
            return false;
        }
        m_pointeurClass.pi_debug = &m_debug;
        m_pointeurClass.pi_settingManager = &m_settingManager;
        if(!m_renderingEngine.initialize(&m_pointeurClass))
        {
            Debug::INITFAILED("RenderingEngine");
            return false;
        }
        m_VulkanMisc = m_renderingEngine.getVulkanMisc();
        return true;
    }

    void GameEngine::release()
    {        
		m_renderingEngine.release();
        m_settingManager.release();
        m_debug.release();
        Debug::RELEASESUCCESS("GameEngine");
    }

    void GameEngine::start()
    {
        Debug::Info("Moteur Start");
        GameEngine::update();
    }
    
    void GameEngine::update()
    {
        while (!glfwWindowShouldClose(m_VulkanMisc->str_VulkanDeviceMisc->str_window))/*gestion d'evenement lier a la fermeture de la fenetre via la croix */
		{
			glfwPollEvents();/*event de recuperation*/
		}
    }
}