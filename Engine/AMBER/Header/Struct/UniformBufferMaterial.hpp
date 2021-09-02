#ifndef __ENGINE_UNIFORM_BUFFER_MATERIAL__
#define __ENGINE_UNIFORM_BUFFER_MATERIAL__

#include "glm/glm.hpp"

struct UniformBufferMaterial
{
    alignas(glm::vec3) glm::vec3 albedo;
    alignas(glm::vec2) glm::vec2 offset;
    alignas(float) float metallic;
    alignas(float) float hdr;
    alignas(float) float normal;
    alignas(float) float ao;
    alignas(int) int albedoMap;
    alignas(int) int normalMap;
    alignas(int) int metallicMap;
    alignas(int) int hdrMap;
    alignas(int) int aoMap;
    alignas(bool) bool light;
};

#endif //__ENGINE_UNIFORM_BUFFER_MATERIAL__