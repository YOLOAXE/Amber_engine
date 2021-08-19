#include "CameraManager.hpp"

namespace Ge
{
    bool CameraManager::initialize(VulkanMisc *vM, I_InputManager *im)
    {
        Debug::INITSUCCESS("CameraManager");
        vulkanM = vM;
        m_flyCamera = new FlyCamera(vM, im);        
        m_Camera[(I_Camera *)m_flyCamera] = (Camera *)m_flyCamera;
        CameraManager::updatePriorityCamera(); 
        std::vector<VkDescriptorBufferInfo> bufferInfo;
        VkDescriptorBufferInfo bufferI{};
        bufferI.buffer = currentCamera->getUniformBuffer().buffer;
        bufferI.offset = 0;
        bufferI.range = sizeof(UniformBufferCamera);
        bufferInfo.push_back(bufferI);        
        m_descriptor->updateCount(vM,1,bufferInfo);               
        return true;
    }

    I_Camera *CameraManager::createCamera(std::string name = "Camera")
    {
        Camera * cam = new Camera(vulkanM);
		m_Camera[(I_Camera *)cam] = cam;
		cam->setName(name);
		CameraManager::updatePriorityCamera();
		return cam;
    }
    
    void CameraManager::releaseCamera(I_Camera *camera)
    {
        Camera * cam = m_Camera[camera];
        m_Camera.erase(camera);
        delete (cam);				
        CameraManager::updatePriorityCamera();
    }
    void CameraManager::updateAspectRatio()
    {
        currentCamera->updatePerspective();
    }
    void CameraManager::updatePriorityCamera()
    {
        int minimum = INT_MAX;
        for (std::map<I_Camera *, Camera *>::iterator iter = m_Camera.begin(); iter != m_Camera.end(); ++iter)
		{
		   	if (iter->second->getPriority() < minimum)
			{
				minimum = iter->second->getPriority();
				currentCamera = iter->second;
			}
		}
        currentCamera->updatePerspective();        
    }
    I_Camera *CameraManager::getCurrentCamera()
    {
        return currentCamera;
    }

    void CameraManager::release()
    {
        for (std::map<I_Camera *, Camera *>::iterator iter = m_Camera.begin(); iter != m_Camera.end(); ++iter)
		{
			delete (iter->second);
		}
		m_Camera.clear();
        delete (m_descriptor);
        Debug::RELEASESUCCESS("CameraManager");
    }
}