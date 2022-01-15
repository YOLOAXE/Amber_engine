#include "NetValue.hpp"

/*namespace Ge
{
	template<class T> 
	NetValue<T>::NetValue(float send_time)
	{
		m_send_time = send_time;
		//m_size = sizeof(T);
		//m_adresse = (const void *)m_data;
	}

	template<class T> 
	bool NetValue<T>::change(float time)
	{
		m_time = time;
		if (m_time > m_send_time)
		{
			m_time = 0.0f;
			if (m_changed)
			{
				m_changed = false;
				return true;
			}			
		}
		return false;
	}
}*/