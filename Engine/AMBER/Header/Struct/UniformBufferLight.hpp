#ifndef __ENGINE_UNIFORM_BUFFER_LIGHT__
#define __ENGINE_UNIFORM_BUFFER_LIGHT__

#include "glm/glm.hpp"

struct UniformBufferLight
{
    alignas(16) glm::vec3 position;
    alignas(16) glm::vec3 direction;
    alignas(float) float cutOff;
    alignas(float) float outerCutOff;

    alignas(float) float constant;
    alignas(float) float linear;
    alignas(float) float quadratic;

    alignas(16) glm::vec3 ambient;
    alignas(16) glm::vec3 diffuse;
    alignas(16) glm::vec3 specular;
    alignas(int) int status; //DirLight = 0 ; PointLight = 1 ; SpotLight = 2
};

#endif //__ENGINE_UNIFORM_BUFFER_LIGHT__