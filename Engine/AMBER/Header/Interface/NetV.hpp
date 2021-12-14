#ifndef __ENGINE_INTERFACE_NETWORK_V__
#define __ENGINE_INTERFACE_NETWORK_V__

class NetV
{
public:
	virtual bool change(float time) = 0;	
	size_t getSize()
	{
		return m_size;
	}
	const void * getAddr()
	{
		return m_adresse;
	}
protected:
	const void * m_adresse;
	size_t m_size;
	float m_send_time = 0.0f;
	float m_time = 0.0f;
	bool m_changed = false;
};

#endif //__ENGINE_INTERFACE_NETWORK_V__