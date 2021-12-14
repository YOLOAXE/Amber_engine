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

namespace Ge
{
	class MirrorComponent : public Behaviour
	{
	public:		
		virtual void update();
		void initialise(int id, NetworkCallBack * callBackSend);
		void receive(unsigned char mode, unsigned char indice, const void * data, size_t size);
	protected:
		unsigned short m_id;		
		std::vector<NetV *> m_network_values;
		NetworkCallBack * m_callBackSend;
	private:
		bool m_init = false;
	};
}
#endif //__ENGINE_NETWORK_MIRROR_COMPONENT__