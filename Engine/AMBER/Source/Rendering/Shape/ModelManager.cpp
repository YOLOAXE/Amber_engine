#include "ModelManager.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"
#include <glm/gtx/normal.hpp>

namespace Ge
{
	bool ModelManager::initiliaze(VulkanMisc *vM)
	{
		vulkanM = vM;		
		if (!BufferManager::createBuffer(sizeof(UniformBufferObject), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_vmaUniformBuffers, vM->str_VulkanDeviceMisc))
		{
			Debug::Error("Echec de la creation d'un uniform buffer");
			return false;
		}
		updateDescriptor();
		Debug::INITSUCCESS("ModelManager");
		return true;
	}

	void ModelManager::updateDescriptor()
	{
		std::vector<VkDescriptorBufferInfo> bufferInfoModel{};
		VkDescriptorBufferInfo bufferIM{};
        for (std::map<Shape *, Model *>::iterator iter = m_models.begin(); iter != m_models.end(); ++iter)
        {
            bufferIM.buffer = iter->second->getUniformBuffers();
			bufferIM.offset = 0;
			bufferIM.range = sizeof(UniformBufferObject);
			bufferInfoModel.push_back(bufferIM);
        }
		if(m_models.size() == 0)
		{
			m_descriptor->updateCount(vulkanM,m_models.size(),bufferInfoModel);
		}
		else
		{
			bufferIM.buffer = m_vmaUniformBuffers.buffer;
			bufferIM.offset = 0;
			bufferIM.range = sizeof(UniformBufferObject);
			bufferInfoModel.push_back(bufferIM);
        	m_descriptor->updateCount(vulkanM,1,bufferInfoModel);
		}
	}

	void ModelManager::release()
	{
		for (std::map<ShapeBuffer *, ModelBuffer *>::iterator iter = m_modelBuffers.begin(); iter != m_modelBuffers.end(); ++iter)
		{
			delete (iter->second);
		}
		m_modelBuffers.clear();
		for (std::map<Shape *, Model *>::iterator iter = m_models.begin(); iter != m_models.end(); ++iter)
		{
			delete (iter->second);
		}
		m_models.clear();
		BufferManager::destroyBuffer(m_vmaUniformBuffers);
		delete(m_descriptor);
		Debug::RELEASESUCCESS("ModelManager");
	}

	Model * ModelManager::createModel(ShapeBuffer *buffer, std::string nom)
	{
		ModelBuffer * mb = m_modelBuffers[buffer];
		if (!mb)
		{
			Debug::Warn("Le buffer n'existe pas");
			return nullptr;
		}
		Model * Mesh = new Model(mb, m_models.size(), vulkanM);
		Mesh->setName(nom);
		m_models[(Model *)Mesh] = Mesh;
		vulkanM->str_VulkanDescriptor->modelCount = m_models.size();
		updateDescriptor();
		return Mesh;
	}

	void ModelManager::destroyModel(Model *model)
	{
		Model * m = m_models[model];
        m_models.erase(model);
        delete (m);
		vulkanM->str_VulkanDescriptor->modelCount = m_models.size();
		updateDescriptor();
	}

	void ModelManager::destroyBuffer(ShapeBuffer *buffer)
	{
		ModelBuffer * mb = m_modelBuffers[buffer];
        m_modelBuffers.erase(buffer);
        delete (mb);
		//TODO detruire les models Lier au buffer
	}

	ShapeBuffer *ModelManager::allocateBuffer(const char *path)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		glm::vec3 normalResult;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path))
		{
			Debug::Warn("%s  %s", nullptr, warn.c_str(), err.c_str());
			return nullptr;
		}

		std::unordered_map<Vertex, uint32_t> uniqueVertices{};

		for (const auto &shape : shapes)
		{
			for (const auto &index : shape.mesh.indices)
			{
				Vertex vertex{};

				vertex.pos = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]};

				vertex.texCoord = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]};

				vertex.normal = {
					attrib.normals[3 * index.normal_index + 0],
					attrib.normals[3 * index.normal_index + 1],
					attrib.normals[3 * index.normal_index + 2]};

				if (uniqueVertices.count(vertex) == 0)
				{
					uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}

				indices.push_back(uniqueVertices[vertex]);
			}
		}

		ModelBuffer *buffer = new ModelBuffer(vertices, indices, vulkanM);
		m_modelBuffers[(ShapeBuffer *)buffer] = buffer;
		return buffer;
	}
}