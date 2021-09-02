#ifndef __ENGINE_MODEL_MANAGER___
#define __ENGINE_MODEL_MANAGER___

#include "VulkanMisc.hpp"
#include "Debug.hpp"
#include <map>
#include "ShapeBuffer.hpp"
#include "Model.hpp"
#include <unordered_map>
#include "Descriptor.hpp"
#include "UniformBufferObject.hpp"

namespace Ge
{
    class ModelManager
    {
    public:
        bool initiliaze(VulkanMisc *vM);
        void release();
        ShapeBuffer *allocateBuffer(const char *path);
        Model *createModel(ShapeBuffer *buffer, std::string nom = "Model");
        void destroyModel(Model *model);
        void destroyBuffer(ShapeBuffer *buffer);
        void updateDescriptor();
		static void InitDescriptor(VulkanMisc * vM);
		static Descriptor* GetDescriptor();
		static std::vector<Model *> GetModels();
    private:
		static std::vector<Model *> m_models;
        std::vector<ShapeBuffer *> m_shapeBuffers;        
        VmaBuffer m_vmaUniformBuffers;
        VulkanMisc *vulkanM;
        static Descriptor *m_descriptor;
    };
}

#endif //__ENGINE_MODEL_MANAGER___