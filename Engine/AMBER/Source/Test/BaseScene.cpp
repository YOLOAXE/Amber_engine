#include "BaseScene.hpp"


void BaseScene::load()
{
	m_ptrc = GameEngine::getPtrClass();
	m_ptrc.skyboxManager->loadSkybox(m_ptrc.textureManager->createTextureCubeMap("../Texture/galaxy.png"));	
	m_ptrc.cameraManager->getCurrentCamera()->setFieldOfView(90.0f);

	GraphiquePipeline* gpunlit = m_ptrc.graphiquePipelineManager->createPipeline("../Shader/frag_unlit.spv", "../Shader/vert_unlit.spv");
	
	ShapeBuffer* cristalsb = m_ptrc.modelManager->allocateBuffer("../Model/cristalbase.obj");
	Materials* cristalmat = m_ptrc.materialManager->createMaterial();
	Model* cristalm = m_ptrc.modelManager->createModel(cristalsb);

	cristalmat->setAlbedoTexture(m_ptrc.textureManager->createTexture("../Texture/cristal/1.3_Material.001_BaseColor.png"));
	cristalmat->setNormalTexture(m_ptrc.textureManager->createTexture("../Texture/cristal/1.3_Material.001_Normal.png"));
	cristalmat->setRoughnessTexture(m_ptrc.textureManager->createTexture("../Texture/cristal/1.3_Material.001_Roughness.png"));
	cristalmat->setRoughness(0.15f);
	cristalmat->setMetallic(0.1f);
	cristalmat->setColor(glm::vec3(214.0f / 255.0f, 47.0f / 255.0f, 47.0f / 255.0f));
	cristalm->setMaterial(cristalmat);

	ShapeBuffer* particleSb = m_ptrc.modelManager->allocateBuffer("../Model/particle.obj");
	Materials* particlemat = m_ptrc.materialManager->createMaterial();
	particlemat->setPipeline(gpunlit);
	particlemat->setColor(glm::vec3(72.0f / 255.0f, 48.0f / 255.0f, 1.0f));
	Model* particlem = m_ptrc.modelManager->createModel(particleSb);
	particlem->setPosition(glm::vec3(0, 10, 20));
	particlem->setMaterial(particlemat);

	ShapeBuffer* kirbySb = m_ptrc.modelManager->allocateBuffer("../Model/kirby.obj");
	Materials* kirbymat = m_ptrc.materialManager->createMaterial();
	kirbymat->setAlbedoTexture(m_ptrc.textureManager->createTexture("../Texture/Texture.tga.png"));
	Model* kirbym = m_ptrc.modelManager->createModel(kirbySb);
	kirbym->setPosition(glm::vec3(0, 5, 15));
	kirbym->setMaterial(kirbymat);
	kirbymat->setRoughness(0.6f);

	ShapeBuffer* starSb = m_ptrc.modelManager->allocateBuffer("../Model/star.obj");
	Materials* starmat = m_ptrc.materialManager->createMaterial();
	starmat->setPipeline(gpunlit);
	starmat->setAlbedoTexture(m_ptrc.textureManager->createTexture("../Texture/Texture.tga.png"));
	Model* starm = m_ptrc.modelManager->createModel(starSb);
	starm->setPosition(glm::vec3(0, 5, 15));
	starm->setMaterial(starmat);

	ShapeBuffer* waterSb = m_ptrc.modelManager->allocateBuffer("../Model/waterplane.obj");
	Materials* watermat = m_ptrc.materialManager->createMaterial();
	Model* waterm = m_ptrc.modelManager->createModel(waterSb);
	watermat->setMetallic(0.0f);
	watermat->setRoughness(0.1f);
	watermat->setColor(glm::vec3(0.2f, 0.3f, 1.0f));	
	GraphiquePipeline* gpwater = m_ptrc.graphiquePipelineManager->createPipeline("../Shader/water_fs.spv", "../Shader/water_vs.spv",false,true,true);
	watermat->setPipeline(gpwater);
	waterm->setMaterial(watermat);

	/*ShapeBuffer* sb = m_ptrc.modelManager->allocateBuffer("../Model/cube.obj");
	
	Materials* mat = m_ptrc.materialManager->createMaterial();
	Materials* mat2 = m_ptrc.materialManager->createMaterial();
	mat2->setPipeline(gp);
	//mat->setShadowCast(false);
	mat->setRoughness(0.3f);
	mat->setMetallic(1.0f);
	Model* m1 = m_ptrc.modelManager->createModel(sb);
	m1->setScale(glm::vec3(10.0f, 1, 10.0f));
	m1->setMaterial(mat);
	Model* m2 = m_ptrc.modelManager->createModel(sb);
	m2->setPosition(glm::vec3(0, 5, 0));
	Model* m3 = m_ptrc.modelManager->createModel(sb);
	m3->setPosition(glm::vec3(-12.0f, 2.0f, -12.0f));	
	m3->setMaterial(mat2);*/

	m_ptrc.lightManager->createPointLight(glm::vec3(10, 10, 10), glm::vec3(1.0, 0.2, 0.3))->setRange(200.0f);
	m_ptrc.lightManager->createPointLight(glm::vec3(-10, 10, 10), glm::vec3(0.10, 0.15, 1.0))->setRange(200.0f);
	m_ptrc.lightManager->createPointLight(glm::vec3(10, 10, -10), glm::vec3(0.35, 1.0, 0.25))->setRange(200.0f);
	m_ptrc.lightManager->createPointLight(glm::vec3(-10, 10, -10), glm::vec3(1.0, 0.5, 0.8))->setRange(200.0f);
	m_ptrc.lightManager->createPointLight(glm::vec3(0, 8, 25), glm::vec3(1.0, 1.0, 0.3))->setRange(200.0f);
}

void BaseScene::unload()
{

}
