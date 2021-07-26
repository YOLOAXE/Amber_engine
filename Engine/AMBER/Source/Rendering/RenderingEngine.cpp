#include "RenderingEngine.hpp"

namespace Ge
{
    RenderingEngine::RenderingEngine()
    {
        m_vulkanMisc.str_VulkanDeviceMisc = &m_vulkanDeviceMisc;
        m_vulkanMisc.str_VulkanSwapChainMisc = &m_vulkanSwapChainMisc;
    }

    bool RenderingEngine::initialize(ptrClass * p_ptrClass)
    {
        if(p_ptrClass == nullptr)
        {
            Debug::Error("ptrClass nullptr RenderingEngine");
            return false;
        }
        Debug::Info("Initialisation du moteur de rendu");
		if (!RenderingEngine::m_window.initialize(p_ptrClass->pi_settingManager->getWindowWidth(), p_ptrClass->pi_settingManager->getWindowHeight(), p_ptrClass->pi_settingManager->getName(), &m_vulkanMisc))
		{
			Debug::INITFAILED("Window");
			return false;
		}
		if (!RenderingEngine::m_instanceVulkan.initialize(p_ptrClass->pi_settingManager->getName(), p_ptrClass->pi_settingManager->getVersion(), &m_vulkanMisc))
		{
			Debug::INITFAILED("InstanceVulkan");
			return false;
		}
		if (!RenderingEngine::m_validationLayer.initialize(&m_vulkanMisc))
		{
			Debug::INITFAILED("ValidationLayer");
			return false;
		}
        if(!RenderingEngine::m_windowSurface.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("WindowSurface");
            return false;
        }
        Debug::INITSUCCESS("RenderingEngine");
        return true;
    }

    void RenderingEngine::release()
    {
        RenderingEngine::m_windowSurface.release();
        RenderingEngine::m_validationLayer.release();
		RenderingEngine::m_instanceVulkan.release();
		RenderingEngine::m_window.release();
        Debug::RELEASESUCCESS("RenderingEngine");
    }

    VulkanMisc * RenderingEngine::getVulkanMisc()
    {
        return &m_vulkanMisc;
    }
}