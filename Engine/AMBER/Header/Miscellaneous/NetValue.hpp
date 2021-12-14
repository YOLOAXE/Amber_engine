#ifndef __ENGINE_NETWORK_MIRROR_VALUE__
#define __ENGINE_NETWORK_MIRROR_VALUE__

#include "NetV.hpp"

namespace Ge
{
	template<class T>
	class NetValue : public NetV
	{
	public:
		NetValue(float send_time = 0);
		bool change(float time);
		T operator=(T d)
		{
			m_changed = m_data == d;
			m_data = d;
		}
	private:
		T m_data;
	};
}
#endif //__ENGINE_NETWORK_MIRROR_VALUE__