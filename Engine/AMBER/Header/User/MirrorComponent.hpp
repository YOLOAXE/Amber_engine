#ifndef __ENGINE_NETWORK_MIRROR_COMPONENT__
#define __ENGINE_NETWORK_MIRROR_COMPONENT__
#include <vector>
#include "NetV.hpp"
#include "Behaviour.hpp"
#include "NetworkCallBack.hpp"

#define MAX_NET_VALUE_COUNT 64
#define MODE_VARIABLE 0
#define MODE_FONCTION 1
#define MODE_INSTANCE 2
#define MODE_DESTROY 3

namespace Ge
{
	class MirrorComponent : public Behaviour
	{
	public:		
		void start();
		void fixedUpdate();
		void update();
		void stop();		
		virtual void mirrorStart() = 0;
		virtual void mirrorFixedUpdate() = 0;
		virtual void mirrorUpdate() = 0;
		virtual void mirrorStop() = 0;
		void initialise(unsigned short id, unsigned short instanceId,bool isOwner, NetworkCallBack * callBackSend);
		void receive(unsigned char mode, unsigned char indice, const void * data, size_t size);
		unsigned short getIdN();
		unsigned short getIDInstance();
	protected:
		unsigned short m_id;	
		unsigned short m_instanceId;
		bool m_isOwner = false;		
		std::vector<NetV *> m_network_values;
		NetworkCallBack * m_callBackSend;
	private:
		bool m_init = false;	
		bool m_isStart = false;
	};
}
#endif //__ENGINE_NETWORK_MIRROR_COMPONENT__