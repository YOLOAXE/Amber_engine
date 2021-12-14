#include "Player.hpp"
#include <sstream>

void Player::start()
{
	sb = GameEngine::getPtrClass().modelManager->allocateBuffer("../Model/cube.obj");
	std::ostringstream sstream;
	sstream << "Player" << m_id;
	std::string name = sstream.str();
	m = GameEngine::getPtrClass().modelManager->createModel(sb, name);
	m->getMaterial()->setColor(glm::vec3(1, 0, 0));
}

void Player::fixedUpdate()
{

}

void Player::update()
{
	MirrorComponent::update();
}

void Player::stop()
{

}

void Player::onGUI()
{

}