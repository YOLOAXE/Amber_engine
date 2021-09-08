#ifndef __ENGINE_SETTING_INFO__
#define __ENGINE_SETTING_INFO__

#include <glm/glm.hpp>
#include "Version.hpp"

struct SettingInfo
{
    double m_fps = 60;
    double m_sizeHeightWindow = 800;
    double m_sizeWidthWindow = 1200;
    const char *m_name = "ProjectName";
    float m_gamma = 1.0f;
    glm::vec3 m_gravity = glm::vec3(0, -9.81f, 0);
    Version m_version;
	glm::vec4 m_clearColor = glm::vec4(0.1f);
};

#endif //__ENGINE_SETTING_INFO__