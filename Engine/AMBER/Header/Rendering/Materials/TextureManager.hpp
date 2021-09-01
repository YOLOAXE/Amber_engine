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
        Texture * createTexture(const char * path);
		void destroyTexture(Texture * texture);
		static void InitDescriptor(VulkanMisc * vM);
    private:
        VulkanMisc *vulkanM;
        std::map<Texture *,Textures *> m_textures;
		Textures * nullTexture;
	private:
		friend class Textures;
        static Descriptor * m_descriptor;
    };
}

#endif //__ENGINE_TEXTURE_MANAGER__