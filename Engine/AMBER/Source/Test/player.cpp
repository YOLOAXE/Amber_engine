#include "Player.hpp"
#include <sstream>

void Player::mirrorStart()
{
	sb = GameEngine::getPtrClass().modelManager->allocateBuffer("../Model/cube.obj");
	std::ostringstream sstream;
	sstream << "Player" << m_id;
	std::string name = sstream.str();
	m = GameEngine::getPtrClass().modelManager->createModel(sb, name);
	m->getMaterial()->setColor(glm::vec3(1, 0, 0));
	m->setScale(glm::vec3(3));
	m_network_values.push_back(new NetValue<float>());
	if (m_isOwner)
	{
		Debug::Log("%s est mon proprietaire", name.c_str());
	}
}

void Player::mirrorUpdate()
{
	if (m_isOwner)
	{
		m->setPosition(-GameEngine::getPtrClass().cameraManager->getCurrentCamera()->getPosition());
	}
}

void Player::mirrorFixedUpdate()
{

}

void Player::mirrorStop()
{
	GameEngine::getPtrClass().modelManager->destroyModel(m);
	GameEngine::getPtrClass().modelManager->destroyBuffer(sb);
}

void Player::onGUI()
{

}