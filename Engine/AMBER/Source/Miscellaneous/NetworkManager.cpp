#include "NetworkManager.hpp"

namespace Ge
{
	bool NetworkManager::initialize(bool host, const char* ipAdress, int threadNum, int port)
	{
		if (!m_isInit)
		{			
			m_host = host;
			m_port = port;
			m_ipAdress = ipAdress;
			if (host)
			{
				int listenfd = srv.createsocket(port);
				if (listenfd < 0) {
					Debug::Error("Echec de la creation d'un serveur tcp");
					return false;
				}
				m_file_descriptor = listenfd;
				Debug::Info("server listen on port %d, listenfd=%d ...\n", port, listenfd);
				srv.onConnection = [](const SocketChannelPtr& channel) {
					std::string peeraddr = channel->peeraddr();
					if (channel->isConnected()) {
						Debug::Info("%s connected! connfd=%d\n", peeraddr.c_str(), channel->fd());
					}
					else {
						Debug::Info("%s disconnected! connfd=%d\n", peeraddr.c_str(), channel->fd());
					}
				};
				srv.onMessage = [](const SocketChannelPtr& channel, Buffer* buf) {
					//Debug::Info("%d < %.*s", channel->fd(), (int)buf->size(), (char*)buf->data());
				};
				srv.setThreadNum(threadNum);
				srv.start();
			}
			else
			{
				int connfd = cli.createsocket(port);
				if (connfd < 0) {
					Debug::Error("client createsocket");
					return false;
				}
				m_file_descriptor = connfd;
				cli.onConnection = [](const SocketChannelPtr& channel) {
					std::string peeraddr = channel->peeraddr();
					if (channel->isConnected()) {
						Debug::Info("connected to %s! connfd=%d\n", peeraddr.c_str(), channel->fd());						
					}
					else {
						Debug::Info("disconnected to %s! connfd=%d\n", peeraddr.c_str(), channel->fd());
					}
				};
				cli.onMessage = [](const SocketChannelPtr& channel, Buffer* buf) {
					//Debug::Info("%d < %.*s", channel->fd(), (int)buf->size(), (char*)buf->data());
				};
				cli.start();
			}
			m_isInit = true;
			return true;
		}
		return true;
	}

	void NetworkManager::callBackSend(unsigned short id, unsigned char mode, unsigned char indice, const void * data, size_t size)
	{

	}

	MirrorComponent * NetworkManager::createObject(unsigned short id)
	{
		MirrorComponent * mc = nullptr;
		if (id < m_allObject.size())
		{
			mc = m_allObject[id]();
			mc->initialise(m_mirrorICount++, (NetworkCallBack *)this);
			m_mirrorObject[mc] = id;
		}
		return mc;
	}

	void NetworkManager::addObject(const mirrorInstanceGenerator& mirrorCreate)
	{
		if (!m_isInit)
		{
			m_allObject[m_objectICount++] = mirrorCreate;
		}
	}

	NetworkManager::~NetworkManager()
	{
		if (m_host)
		{
			srv.closesocket();
		}
		else
		{
			cli.closesocket();
		}
		m_allObject.clear();
	}
}