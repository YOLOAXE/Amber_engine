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
        m_pointeurClass.pi_inputManager = &m_inputManager;
        if(!m_renderingEngine.initialize(&m_pointeurClass))
        {
            Debug::INITFAILED("RenderingEngine");
            return false;
        }        
        m_VulkanMisc = m_renderingEngine.getVulkanMisc();
        if(!m_inputManager.initialize(m_VulkanMisc))
        {
            Debug::INITFAILED("InputManager");
            return false;
        }
        return true;
    }

    void GameEngine::release()
    {        
		m_renderingEngine.release();
        m_settingManager.release();
        m_debug.release();
        m_time.release();
        m_inputManager.release();
        Debug::RELEASESUCCESS("GameEngine");
    }

    void GameEngine::start()
    {
        Debug::Info("Moteur Start");
        m_time.startTime();
        GameEngine::update();
    }
    
    void GameEngine::update()
    {
        while (!glfwWindowShouldClose(m_VulkanMisc->str_VulkanDeviceMisc->str_window))/*gestion d'evenement lier a la fermeture de la fenetre via la croix */
		{
			glfwPollEvents();/*event de recuperation*/
            m_time.fixedUpdateTime();
			m_lag += m_time.getFixedDeltaTime();						
			if (m_lag >= 1/m_settingManager.getFps())
			{
				m_time.updateTime();				
				m_renderingEngine.drawFrame();
				m_lag -= 1/m_settingManager.getFps();
			}
		}
    }
}