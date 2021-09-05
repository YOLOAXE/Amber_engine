#ifndef __ENGINE_UNIFORM_BUFFER_MATERIAL__
#define __ENGINE_UNIFORM_BUFFER_MATERIAL__

#include "glm/glm.hpp"

struct UniformBufferMaterial
{
    glm::vec3 albedo;
	alignas(16) glm::vec2 offset;
    float metallic;
    float hdr;
    float normal;
    float ao;
    int albedoMap;
    int normalMap;
    int metallicMap;
    int hdrMap;
    int aoMap;
    int light;
};

#endif //__ENGINE_UNIFORM_BUFFER_MATERIAL__