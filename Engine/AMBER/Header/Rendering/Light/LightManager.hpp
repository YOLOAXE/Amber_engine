#ifndef __ENGINE_LIGHT_MANAGER__
#define __ENGINE_LIGHT_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"
#include "DirectionalLight.hpp"
#include "Descriptor.hpp"

namespace Ge
{
    class LightManager
    {
    public:
        bool initialize(VulkanMisc *vM);
        void release();
        SpotLight *createSpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutOff, float outerCutOff, std::string name = "SpotLight");
        DirectionalLight *createDirectionalLight(glm::vec3 direction, glm::vec3 color, std::string name = "DirectionalLight");
        PointLight *createPointLight(glm::vec3 position, glm::vec3 color, std::string name = "PointLight");
        void destroyLight(Lights *light);
        void updateDescriptor();
        void majIndex();
		static void InitDescriptor(VulkanMisc * vM);
		static Descriptor* GetDescriptor();
    private:
        VulkanMisc *vulkanM;
        std::vector<Lights *> m_lights;
        VmaBuffer m_vmaUniformBuffers;
        static Descriptor * m_descriptor;
    };
}

#endif //__ENGINE_LIGHT_MANAGER__