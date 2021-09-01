#ifndef __ENGINE_LIGHT_MANAGER__
#define __ENGINE_LIGHT_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include "Vector3.hpp"
#include "LPoint.hpp"
#include "LSpot.hpp"
#include "LDirectional.hpp"
#include "Descriptor.hpp"

namespace Ge
{
    class LightManager
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();
        SpotLight *createSpotLight(Vector3 position, Vector3 color, Vector3 direction, float cutOff, float outerCutOff, std::string name = "SpotLight");
        DirectionalLight *createDirectionalLight(Vector3 direction, Vector3 color, std::string name = "DirectionalLight");
        PointLight *createPointLight(Vector3 position, Vector3 color, std::string name = "PointLight");
        void destroyLight(Light *light);
        void updateDescriptor();
        void majIndex();
		static void InitDescriptor(VulkanMisc * vM);
		static Descriptor* GetDescriptor();
    private:
        VulkanMisc *vulkanM;
        std::map<Light *, Lights *> m_mapLights;
        VmaBuffer m_vmaUniformBuffers;
    private:
		friend class Lights;
        static Descriptor * m_descriptor;
    };
}

#endif //__ENGINE_LIGHT_MANAGER__