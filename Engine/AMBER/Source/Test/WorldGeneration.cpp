#include "WorldGeneration.hpp"

namespace lia
{
    void WorldGeneration::load()
    {
        Debug::Log("Load world Generation");
        GameEngine::getPtrClass().skyboxManager->loadSkybox(GameEngine::getPtrClass().textureManager->createTextureCubeMap("../Texture/skybox.png"));
        float pos[12] = {
            -1,0,1,1,0,1,-1,0,-1,1,0,-1
        };
        float texCord[8] = {
            0,1,1,1,0,0,1,0
        };
        float normal[12] = {
            0,1,0,0,1,0,0,1,0,0,1,0
        };
        unsigned int indice[6] = {
            0,1,2,1,3,2
        };
        //ShapeBuffer * sb = GameEngine::getPtrClass().modelManager->allocateBuffer("../Model/quad.obj");        
        ShapeBuffer * sb = GameEngine::getPtrClass().modelManager->allocateBuffer(pos,texCord,normal,indice,4,6);                
        Model * m = GameEngine::getPtrClass().modelManager->createModel(sb);
        Materials * mat = GameEngine::getPtrClass().materialManager->createMaterial();
        mat->setAlbedoTexture(GameEngine::getPtrClass().textureManager->createTexture("../Texture/ZombieRLTileset.png"));        
        m->setMaterial(mat);
        Camera * c = GameEngine::getPtrClass().cameraManager->getCurrentCamera();
        c->setPosition(glm::vec3(-0.742f,-2.668f,-3.223f));
        c->setEulerAngles(glm::vec3(50.4f,2.0f,0.0f));
        GameEngine::getPtrClass().lightManager->createPointLight(glm::vec3(0,1,0),glm::vec3(1,1,1));
    }

	void WorldGeneration::unload()
    {
        Debug::Log("Unload world Generation");
    }
}