#include "BaseScene.hpp"


void BaseScene::load()
{
	m_ptrc = GameEngine::getPtrClass();
	ShapeBuffer* sb = m_ptrc.modelManager->allocateBuffer("../Model/cube.obj");
	Materials* mat = m_ptrc.materialManager->createMaterial();
	//mat->setShadowCast(false);
	mat->setRoughness(0.5f);
	Model* m1 = m_ptrc.modelManager->createModel(sb);
	m1->setScale(glm::vec3(10.0f, 1, 10.0f));
	m1->setMaterial(mat);
	Model* m2 = m_ptrc.modelManager->createModel(sb);
	m2->setPosition(glm::vec3(0, 5, 0));
	Model* m3 = m_ptrc.modelManager->createModel(sb);
	m3->setPosition(glm::vec3(-12.0f, 2.0f, -12.0f));

	//Lights* l = m_ptrc.lightManager->createDirectionalLight(glm::vec3(-45, 45, 0), glm::vec3(0.8f, 0.8f, 1.0f));
	//l->setShadow(true);
	Lights* spot = m_ptrc.lightManager->createSpotLight(glm::vec3(5, 10, 5), glm::vec3(1, 1, 1), glm::vec3(-45, 45, 0),45.0f);
	spot->setShadow(true);	
}

void BaseScene::unload()
{

}
