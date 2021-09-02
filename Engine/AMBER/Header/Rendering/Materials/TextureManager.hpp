#ifndef __ENGINE_TEXTURE_MANAGER__
#define __ENGINE_TEXTURE_MANAGER__

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include "Textures.hpp"
#include <map>
#include "Descriptor.hpp"

namespace Ge
{
    class TextureManager
    {
    private:
        friend class RenderingEngine;
        bool initiliaze(VulkanMisc *vM);
        void release();   
        void updateDescriptor();     
    public:
        Textures * createTexture(const char * path);
		void destroyTexture(Textures * texture);
		static void InitDescriptor(VulkanMisc * vM);
		static Descriptor* GetDescriptor();
    private:
        VulkanMisc *vulkanM;
        std::vector<Textures *> m_textures;
		Textures * nullTexture;
        static Descriptor * m_descriptor;
    };
}

#endif //__ENGINE_TEXTURE_MANAGER__