#ifndef __ENGINE_INTERFACE_NETWORK_CALLBACK__
#define __ENGINE_INTERFACE_NETWORK_CALLBACK__

class NetworkCallBack
{
public:
	virtual void callBackSend(unsigned short id, unsigned char mode, unsigned char indice, const void * data, size_t size) = 0;
};


#endif //__ENGINE_INTERFACE_NETWORK_CALLBACK__