#ifndef __ENGINE_PUSH_CONSTANTS__
#define __ENGINE_PUSH_CONSTANTS__

struct PushConstants
{
    alignas(int) int ubo;
    alignas(int) int material;
};

#endif //__ENGINE_PUSH_CONSTANTS__