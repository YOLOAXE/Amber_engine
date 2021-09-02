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
        bool initialize(VulkanMisc *vM, InputManager *input);
        void release();
        Camera *createCamera(std::string name = "Camera");
        void releaseCamera(Camera *camera);
        void updateAspectRatio();
        static void updatePriorityCamera();
        Camera *getCurrentCamera();
		static void InitDescriptor(VulkanMisc * vM);
		static Descriptor* GetDescriptor();        
    private:
		static Descriptor * m_descriptor;
        static std::vector<Camera *> m_cameras;
        static Camera *currentCamera;
        VulkanMisc * vulkanM;        
        FlyCamera * m_flyCamera;
    };
}

#endif //__ENGINE_CAMERA_MANAGER__