#ifndef __ENGINE_SETTING_INFO__
#define __ENGINE_SETTING_INFO__

#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Version.hpp"

struct SettingInfo
{
    double m_fps = 60;
    double m_sizeHeightWindow = 800;
    double m_sizeWidthWindow = 1200;
    const char *m_name = "ProjectName";
    float m_gamma = 1.0f;
    Vector3 m_gravity = Vector3(0, -9.81f, 0);
    Version m_version;
    Vector4 m_clearColor = Vector4(1.0f);
};

#endif //__ENGINE_SETTING_INFO__