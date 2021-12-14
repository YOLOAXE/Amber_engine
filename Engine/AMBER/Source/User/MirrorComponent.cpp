#include "MirrorComponent.hpp"
#include "GameEngine.hpp"

namespace Ge
{
	void MirrorComponent::update()
	{
		for (unsigned char i = 0; i < m_network_values.size() && m_init;i++)
		{
			if (m_network_values[i]->change(GameEngine::getPtrClass().time->getDeltaTime()))
			{
				m_callBackSend->callBackSend(m_id, MODE_VARIABLE,i, m_network_values[i]->getAddr(), m_network_values[i]->getSize());
			}
		}
	}

	void MirrorComponent::initialise(int id, NetworkCallBack * callBackSend)
	{
		m_id = id;
		m_callBackSend = callBackSend;
		m_init = true;
	}

	void MirrorComponent::receive(unsigned char mode, unsigned char indice, const void * data, size_t size)
	{

	}
}