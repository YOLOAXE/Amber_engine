#include "NetworkManager.hpp"
#include "GameEngine.hpp"

namespace Ge
{
	NetworkManager * NetworkManager::m_NetworkManager = nullptr;
	NetworkManager::NetworkManager()
	{
		m_NetworkManager = this;
	}

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
						NetworkManager::m_NetworkManager->Connection(channel);
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
				MirrorComponent * mc = m_NetworkManager->createObject(0, 0);	
				m_fd_link[m_file_descriptor] = m_mirrorICount++;
				GameEngine::getPtrClass().behaviourManager->addBehaviour(mc);
				m_isInit = true;
				return true;
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
					Debug::Info("%d", (int)buf->size());
					NetworkManager::Message(buf->data(), buf->size());
				};
				cli.start();
			}
			m_isInit = true;
			return true;
		}
		return true;
	}

	void NetworkManager::Connection(const SocketChannelPtr& channel)
	{
		size_t size = 5;
		char * data = (char *)malloc(size);
		m_NetworkManager->m_fd_link[channel->fd()] = m_NetworkManager->m_mirrorICount++;
		unsigned short id;
		unsigned char mode, instance;
		unsigned char* id_p;	
		mode = MODE_INSTANCE;
		data[2] = mode;
		data[4] = 0;
		for (const auto&[key, value] : m_NetworkManager->m_mirrorObject)
		{			
			id = key->getIdN();			
			instance = value;
			id_p = reinterpret_cast<unsigned char*>(&id);
			data[0] = id_p[0];
			data[1] = id_p[1];			
			data[3] = instance;					
			channel->write((void *)data, size);
		}		
		id = m_NetworkManager->m_fd_link[channel->fd()];
		instance = 0;//Player
		id_p = reinterpret_cast<unsigned char*>(&id);
		data[0] = id_p[0];
		data[1] = id_p[1];
		data[3] = instance;
		m_NetworkManager->srv.broadcast((void *)data, size);
		Message((void *)data, size);
		free(data);
	}

	void NetworkManager::Message(void * data,int size)
	{
		unsigned char * dataChar = (unsigned char*)data;
		unsigned char * id_p = (unsigned char *)malloc(sizeof(unsigned short));
		int globalSize = size;
		unsigned short * id = reinterpret_cast<unsigned short*>(id_p);
		unsigned char mode, instance, readsize;
		int countElement = 0;
		while (globalSize > 0)
		{
			id_p[0]  = dataChar[countElement+0];
			id_p[1]  = dataChar[countElement+1];
			mode     = dataChar[countElement+2];
			instance = dataChar[countElement+3];
			readsize = dataChar[countElement+4];
			Debug::Log("%d %d %d", id[0], mode, instance);
			if (mode == MODE_INSTANCE)
			{
				MirrorComponent * mc = m_NetworkManager->createObject(instance, id[0]);
				if (mc == nullptr)
				{
					Debug::Error("nullptr network");
					return;
				}
				GameEngine::getPtrClass().behaviourManager->addBehaviour(mc);
			}
			globalSize -= 5 + readsize;
			countElement += 5 + readsize;
		}
		free(id_p);
	}

	void NetworkManager::callBackSend(unsigned short id, unsigned char mode, unsigned char indice, const void * data, size_t size)
	{

	}

	MirrorComponent * NetworkManager::createObject(unsigned short id, unsigned short idN)
	{
		MirrorComponent * mc = nullptr;
		if (id < m_allObject.size())
		{
			mc = m_allObject[id]();
			mc->initialise(idN, (NetworkCallBack *)this);
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
		m_mirrorObject.clear();
	}
}