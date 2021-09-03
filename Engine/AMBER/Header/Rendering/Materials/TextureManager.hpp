#ifndef __ENGINE_TEXTURE_MANAGER__
#define __ENGINE_TEXTURE_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include "Textures.hpp"
#include <map>
#include "Manager.hpp"

namespace Ge
{
    class TextureManager : public Manager
    {
    private:
        friend class RenderingEngine;
        bool initiliaze(VulkanMisc *vM);
        void release();                
    public:
        Textures * createTexture(const char * path);
		void destroyTexture(Textures * texture);
		void initDescriptor(VulkanMisc * vM);
		void updateDescriptor();
    private:
        VulkanMisc *vulkanM;
        std::vector<Textures *> m_textures;
		Textures * nullTexture;
    };
}

#endif //__ENGINE_TEXTURE_MANAGER__