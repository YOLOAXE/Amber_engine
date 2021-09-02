#include "CameraManager.hpp"

namespace Ge
{
	Descriptor * CameraManager::m_descriptor = nullptr;	
	Camera *CameraManager::currentCamera = nullptr;
	std::vector<Camera *> CameraManager::m_cameras;

    bool CameraManager::initialize(VulkanMisc *vM, InputManager *im)
    {        
        vulkanM = vM;
        m_flyCamera = new FlyCamera(vM, im);        
		m_cameras.push_back((Camera *)m_flyCamera);
        CameraManager::updatePriorityCamera(); 
        std::vector<VkDescriptorBufferInfo> bufferInfo;
        VkDescriptorBufferInfo bufferI{};
        bufferI.buffer = currentCamera->getUniformBuffer();
        bufferI.offset = 0;
        bufferI.range = sizeof(UniformBufferCamera);
        bufferInfo.push_back(bufferI);
        m_descriptor->updateCount(vM,1,bufferInfo);               
		Debug::INITSUCCESS("CameraManager");
        return true;
    }

    Camera *CameraManager::createCamera(std::string name)
    {
        Camera * cam = new Camera(vulkanM);
		m_cameras.push_back(cam);
		cam->setName(name);
		CameraManager::updatePriorityCamera();
		return cam;
    }
    
    void CameraManager::releaseCamera(Camera *camera)
    {
		m_cameras.erase(std::remove(m_cameras.begin(), m_cameras.end(), camera), m_cameras.end());
        delete (camera);
        CameraManager::updatePriorityCamera();
    }
    void CameraManager::updateAspectRatio()
    {
        currentCamera->updatePerspective();
    }
    void CameraManager::updatePriorityCamera()
    {
        int minimum = INT_MAX;
        for (int i = 0 ; i < m_cameras.size();i++)
		{
		   	if (m_cameras[i]->getPriority() < minimum)
			{
				minimum = m_cameras[i]->getPriority();
				currentCamera = m_cameras[i];
			}
		}
        currentCamera->updatePerspective();        
    }

    Camera *CameraManager::getCurrentCamera()
    {
        return currentCamera;
    }

	void CameraManager::InitDescriptor(VulkanMisc * vM)
	{
		CameraManager::m_descriptor = new Descriptor(vM, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1);
	}

	Descriptor* CameraManager::GetDescriptor()
	{
		return CameraManager::m_descriptor;
	}

    void CameraManager::release()
    {
		if (m_flyCamera != nullptr)
		{
			m_cameras.erase(std::remove(m_cameras.begin(), m_cameras.end(), (Camera *)m_flyCamera), m_cameras.end());
			delete (m_flyCamera);
		}
		for (int i = 0; i < m_cameras.size(); i++)
		{
			delete(m_cameras[i]);
		}
		m_cameras.clear();
        delete (m_descriptor);
        Debug::RELEASESUCCESS("CameraManager");
    }
}