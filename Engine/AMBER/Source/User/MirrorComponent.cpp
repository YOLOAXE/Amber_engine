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
		if (m_isStart)
		{
			mirrorUpdate();
		}
	}

	void MirrorComponent::start()
	{
		mirrorStart();
		m_isStart = true;
	}

	void MirrorComponent::fixedUpdate()
	{
		if (m_isStart)
		{
			mirrorFixedUpdate();
		}
	}

	void MirrorComponent::stop()
	{
		mirrorStop();
		m_isStart = false;
	}

	void MirrorComponent::initialise(unsigned short id, unsigned short instanceId, bool isOwner, NetworkCallBack * callBackSend)
	{
		m_id = id;
		m_instanceId = instanceId;
		m_isOwner = isOwner;
		m_callBackSend = callBackSend;
		m_init = true;
	}

	void MirrorComponent::receive(unsigned char mode, unsigned char indice, const void * data, size_t size)
	{

	}

	unsigned short MirrorComponent::getIdN()
	{
		return m_id;
	}

	unsigned short MirrorComponent::getIDInstance()
	{
		return m_instanceId;
	}
}