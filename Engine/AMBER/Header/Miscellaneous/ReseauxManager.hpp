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
using namespace hv;
#include "Debug.hpp"
#include <iostream>
#include <string>

namespace Ge
{
	class ReseauxManager
	{
	public:
		ReseauxManager(bool host,int port = 25565, const char* ipAdress = "127.0.0.1");
	private:
		TcpServer srv;
		bool m_host = false;
		int m_port;
		const char* m_ipAdress;
	};
}

#endif __ENGINE_RESEAUX_MANAGER__
