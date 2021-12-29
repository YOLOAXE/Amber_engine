#ifndef __ENGINE_RESEAUX_MANAGER__
#define __ENGINE_RESEAUX_MANAGER__

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#elif defined(__APPLE__)
#elif defined(__unix__) || defined(__unix)
#else
#error plate-forme non prise en charge
#endif
#include "hv/include/TcpServer.h"
#include "hv/include/TcpClient.h"
using namespace hv;
#include "Debug.hpp"
#include <iostream>
#include <string>
#include <map>
#include "MirrorComponent.hpp"
#include "NetworkCallBack.hpp"

namespace Ge
{	
	class NetworkManager : public NetworkCallBack
	{
	public:		
		typedef MirrorComponent*(*mirrorInstanceGenerator)();
		NetworkManager();
		bool initialize(bool host, const char* ipAdress = "127.0.0.1", int threadNum = 4, int port = 25565);
		void addObject(const mirrorInstanceGenerator& mirrorCreate);
		MirrorComponent * createObject(unsigned short idInstance, unsigned short idN);
		void callBackSend(unsigned short id, unsigned char mode, unsigned char indice, const void * data, size_t size);
		~NetworkManager();	
		static void Connection(const SocketChannelPtr& channel);
		static void Deconection(const SocketChannelPtr& channel);
		static void Message(void * data, int size);
	private:
		std::map<unsigned short, mirrorInstanceGenerator> m_allObject;
		std::map<unsigned short,MirrorComponent *> m_mirrorObject;
		std::map<int, unsigned short> m_fd_link;
		TcpServer srv;
		TcpClient cli;
		bool m_host = false;
		int m_port;
		const char* m_ipAdress;
		int m_file_descriptor;
		bool m_isInit = false;
		bool m_first = false;
		static NetworkManager * m_NetworkManager;
		unsigned short m_objectICount = 0;
		unsigned short m_mirrorICount = 0;
	};
}

#endif __ENGINE_RESEAUX_MANAGER__
