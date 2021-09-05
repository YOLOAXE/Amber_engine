#ifndef __ENGINE_UNIFORM_BUFFER_LIGHT__
#define __ENGINE_UNIFORM_BUFFER_LIGHT__

#include "glm/glm.hpp"

struct UniformBufferLight
{
    glm::vec3 position;
    alignas(16) glm::vec3 direction;
	alignas(16) float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    alignas(16) glm::vec3 diffuse;
    alignas(16) glm::vec3 specular;
	alignas(16) int status; //DirLight = 0 ; PointLight = 1 ; SpotLight = 2
};

#endif //__ENGINE_UNIFORM_BUFFER_LIGHT__