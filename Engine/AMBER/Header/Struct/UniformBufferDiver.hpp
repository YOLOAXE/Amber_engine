#ifndef __ENGINE_UNIFORM_BUFFER_DIVER__
#define __ENGINE_UNIFORM_BUFFER_DIVER__

struct UniformBufferDiver
{
    alignas(int) int maxLight;
    alignas(float) float u_time;
    alignas(float) float gamma;
};

#endif //__ENGINE_UNIFORM_BUFFER_DIVER__