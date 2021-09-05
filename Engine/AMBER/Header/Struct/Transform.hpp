#ifndef __ENGINE_TRANSFORM__
#define __ENGINE_TRANSFORM__

#include "glm/glm.hpp"

struct Transform
{
    glm::mat4 rotationMatrix;
    glm::mat4 translateMatrix;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 target;
    glm::quat rotation;
    glm::vec3 eulerAngles;
    glm::vec3 scale;
};

#endif //__ENGINE_TRANSFORM__