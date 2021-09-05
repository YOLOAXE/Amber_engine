#include "BehaviourManager.hpp"

namespace Ge
{
	void BehaviourManager::addBehaviour(Behaviour * b)
	{
		m_behaviours.push_back(b);
		b->start();
	}

	void BehaviourManager::removeBehaviour(Behaviour * b)
	{
		b->stop();
		m_behaviours.erase(std::remove(m_behaviours.begin(), m_behaviours.end(), b), m_behaviours.end());
	}

	void BehaviourManager::update()
	{
		for (int i = 0; i < m_behaviours.size(); i++)
		{
			m_behaviours[i]->update();
		}
	}

	void BehaviourManager::fixedUpdate()
	{
		for (int i = 0; i < m_behaviours.size(); i++)
		{
			m_behaviours[i]->fixedUpdate();
		}
	}
}