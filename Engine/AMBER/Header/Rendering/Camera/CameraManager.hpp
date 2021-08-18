#ifndef __ENGINE_CAMERA_MANAGER__
#define __ENGINE_CAMERA_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include "Descriptor.hpp"
#include "UniformBufferCamera.hpp"
#include "FlyCamera.hpp"
#include <map>

namespace Ge
{
    class CameraManager
    {
    public:
        bool initialize(VulkanMisc *vM, I_InputManager *input);
        void release();
        I_Camera *createCamera(std::string name = "Camera");
        void releaseCamera(I_Camera *camera);
        void updateAspectRatio();
        static void updatePriorityCamera();
        I_Camera *getCurrentCamera();

    public:
        static Descriptor *m_descriptor;

    private:
        static std::map<I_Camera *, Camera *> m_Camera;
        static Camera *currentCamera;
        VulkanMisc * vulkanM;        
        FlyCamera * m_flyCamera;
    };
}

#endif //__ENGINE_CAMERA_MANAGER__