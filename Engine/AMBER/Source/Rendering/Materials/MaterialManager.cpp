#include "MaterialManager.hpp"

namespace Ge
{    
    bool MaterialManager::initialize(VulkanMisc *vM)
    {
        Debug::INITSUCCESS("MaterialManager");
        return true;
    }

    void MaterialManager::release()
    {
        delete(m_descriptor);
        Debug::RELEASESUCCESS("MaterialManager");
    }
}