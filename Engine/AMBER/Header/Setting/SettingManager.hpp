#ifndef __ENGINE_SETTING_MANAGER__
#define __ENGINE_SETTING_MANAGER__

#include "Initializer.hpp"
#include "Debug.hpp"
#include "SettingInfo.hpp"
#include "I_SettingManager.hpp"

namespace Ge
{
    class SettingManager : public I_SettingManager, Initializer
    {
    public:
        double getFps();
        void setFps(double fps);
        const char *getName();
        void setName(const char *name);
        double getWindowHeight();
        void setWindowHeight(double height);
        double getWindowWidth();
        void setWindowWidth(double Width);
        Vector3 getGravity();
        void setGravity(Vector3 gravity);
        void setVersion(Version v);
        Version getVersion();
        void setClearColor(Vector4 color);
        Vector4 getClearColor();
        void setGamma(float gamma);
        float getGamma();
        bool initialize();
        void release();

    private:
        SettingInfo m_settingInfo;
    };
}

#endif //__ENGINE_SETTING_MANAGER__