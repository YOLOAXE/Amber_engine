#ifndef __ENGINE_RENDERING_ENGINE__
#define __ENGINE_RENDERING_ENGINE__

#include "Debug.hpp"
#include "PointeurClass.hpp"
#include "InstanceVulkan.hpp"
#include "ValidationLayer.hpp"
#include "Window.hpp"
#include "WindowSurface.hpp"

namespace Ge
{
    class RenderingEngine
    {
    public:
        RenderingEngine();
        bool initialize(ptrClass * p_ptrClass);
        void release();
        VulkanMisc * getVulkanMisc();
    private:
        VulkanMisc m_vulkanMisc;
        VulkanDeviceMisc m_vulkanDeviceMisc;
        VulkanSwapChainMisc m_vulkanSwapChainMisc;

        Window m_window;
        ValidationLayer m_validationLayer;
		InstanceVulkan m_instanceVulkan;
        WindowSurface m_windowSurface;
    };
}

#endif //__ENGINE_RENDERING_ENGINE__