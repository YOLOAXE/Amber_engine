#include "RenderingEngine.hpp"

namespace Ge
{
    RenderingEngine::RenderingEngine()
    {
        m_vulkanMisc.str_VulkanDeviceMisc = &m_vulkanDeviceMisc;
        m_vulkanMisc.str_VulkanSwapChainMisc = &m_vulkanSwapChainMisc;
        m_vulkanMisc.str_VulkanDescriptor = &m_VulkanDescriptor;
        m_vulkanMisc.str_VulkanCommandeBufferMisc = &m_VulkanCommandeBufferMisc;
    }

    bool RenderingEngine::initialize(ptrClass *p_ptrClass)
    {
        if (p_ptrClass == nullptr)
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
        if (!RenderingEngine::m_windowSurface.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("WindowSurface");
            return false;
        }
        if (!RenderingEngine::m_physicalDevice.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("PhysicalDevice");
            return false;
        }
        if (!RenderingEngine::m_logicalDevice.initialize(&m_vulkanMisc, &m_windowSurface))
        {
            Debug::INITFAILED("LogicalDevice");
            return false;
        }
        if (!RenderingEngine::m_commandPool.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("CommandPool");
            return false;
        }
        if (!RenderingEngine::m_bufferManager.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("BufferManager");
            return false;
        }
        if (!RenderingEngine::m_swapChain.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("SwapChain");
            return false;
        }
        if (!RenderingEngine::m_colorResources.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("ColorResources");
            return false;
        }
        if (!RenderingEngine::m_depthResources.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("DepthResources");
            return false;
        }
        if (!RenderingEngine::m_frameBuffers.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("Framebuffers");
            return false;
        }
        if(!RenderingEngine::m_cameraManager.initialize(&m_vulkanMisc, p_ptrClass->pi_inputManager))
        {
            Debug::INITFAILED("CameraManager");
            return false;
        }
        if (!RenderingEngine::m_textureManager.initiliaze(&m_vulkanMisc))
        {
            Debug::INITFAILED("TextureManager");
            return false;
        }
        if (!RenderingEngine::m_modelManager.initiliaze(&m_vulkanMisc))
        {
            Debug::INITFAILED("ModelManager");
            return false;
        }
        if (!RenderingEngine::m_materialManager.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("MaterialManager");
            return false;
        }
        if (!RenderingEngine::m_lightManager.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("LightManager");
            return false;
        }
        if (!RenderingEngine::m_shaderUniformBufferDivers.initialize(&m_vulkanMisc))
        {
            Debug::INITFAILED("ShaderUniformBufferDivers");
            return false;
        }
        if (!RenderingEngine::m_commandBuffer.initialize(&m_vulkanMisc)) {
            Debug::INITFAILED("CommandBuffer");
            return false;
        }
        Debug::INITSUCCESS("RenderingEngine");
        return true;
    }

    void RenderingEngine::release()
    {
        vkDeviceWaitIdle(m_vulkanDeviceMisc.str_device);        
        RenderingEngine::m_shaderUniformBufferDivers.release();
        RenderingEngine::m_lightManager.release();
        RenderingEngine::m_materialManager.release();
        RenderingEngine::m_modelManager.release();
        RenderingEngine::m_textureManager.release();
        RenderingEngine::m_frameBuffers.release();
        RenderingEngine::m_depthResources.release();
        RenderingEngine::m_colorResources.release();
        RenderingEngine::m_swapChain.release();
        RenderingEngine::m_bufferManager.release();
        RenderingEngine::m_commandPool.release();
        RenderingEngine::m_logicalDevice.release();
        RenderingEngine::m_physicalDevice.release();
        RenderingEngine::m_windowSurface.release();
        RenderingEngine::m_validationLayer.release();
        RenderingEngine::m_instanceVulkan.release();
        RenderingEngine::m_window.release();
        Debug::RELEASESUCCESS("RenderingEngine");
    }

    void RenderingEngine::drawFrame()
    {
        
    }

    VulkanMisc *RenderingEngine::getVulkanMisc()
    {
        return &m_vulkanMisc;
    }
}