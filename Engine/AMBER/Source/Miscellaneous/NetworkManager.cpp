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
		if (m_allObject.size() == 0)
		{
			Debug::Error("Echec de l'initialisation 0 MirrorComponent");
			return false;
		}
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
						NetworkManager::m_NetworkManager->Deconection(channel);
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
		unsigned char mode;
		unsigned char* id_p;	
		mode = MODE_INSTANCE;
		data[2] = mode;
		data[4] = 0;
		id = m_NetworkManager->m_fd_link[channel->fd()];
		id_p = reinterpret_cast<unsigned char*>(&id);
		data[0] = id_p[0];
		data[1] = id_p[1];
		data[3] = 0;//player
		m_NetworkManager->srv.broadcast((void *)data, size);
		for (const auto&[key, value] : m_NetworkManager->m_mirrorObject)
		{			
			id = value->getIdN();
			id_p = reinterpret_cast<unsigned char*>(&id);
			data[0] = id_p[0];
			data[1] = id_p[1];			
			data[3] = value->getIDInstance();
			channel->write((void *)data, size);
		}		
		id = m_NetworkManager->m_fd_link[channel->fd()];
		id_p = reinterpret_cast<unsigned char*>(&id);
		data[0] = id_p[0];
		data[1] = id_p[1];
		data[3] = 0;//player		
		Message((void *)data, size);
		free(data);
	}

	void NetworkManager::Deconection(const SocketChannelPtr& channel)
	{
		size_t size = 5;
		char * data = (char *)malloc(size);		
		unsigned short id = m_NetworkManager->m_fd_link[channel->fd()];
		unsigned char* id_p;	
		id_p = reinterpret_cast<unsigned char*>(&id);
		data[0] = id_p[0];
		data[1] = id_p[1];
		data[2] = MODE_DESTROY;
		data[3] = 0;
		data[4] = 0;
		m_NetworkManager->m_fd_link.erase(channel->fd());
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
			else if(mode == MODE_DESTROY)
			{
				if (m_NetworkManager->m_mirrorObject.count(id[0]))
				{
					GameEngine::getPtrClass().behaviourManager->removeBehaviour(m_NetworkManager->m_mirrorObject[id[0]]);
					m_NetworkManager->m_mirrorObject.erase(id[0]);
				}
			}
			globalSize -= 5 + readsize;
			countElement += 5 + readsize;
		}
		free(id_p);
	}

	void NetworkManager::callBackSend(unsigned short id, unsigned char mode, unsigned char indice, const void * data, size_t size)
	{

	}

	MirrorComponent * NetworkManager::createObject(unsigned short idInstance, unsigned short idN)
	{
		MirrorComponent * mc = nullptr;
		if (idInstance < m_allObject.size())
		{
			mc = m_allObject[idInstance]();
			mc->initialise(idN, idInstance,!m_first,(NetworkCallBack *)this);
			m_mirrorObject[idN] = mc;			
			m_first = true;
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
		if (m_isInit)
		{
			if (m_host)
			{
				srv.closesocket();
			}
			else
			{
				cli.closesocket();
			}
		}
		m_allObject.clear();
		m_mirrorObject.clear();
	}
}