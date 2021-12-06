#include "ReseauxManager.hpp"

namespace Ge
{
	ReseauxManager::ReseauxManager(bool host,int port ,const char* ipAdress)
	{
		m_host = host;
		m_port = port;
		m_ipAdress = ipAdress;
		int listenfd = srv.createsocket(port);
		if (listenfd < 0) {
			Debug::Error("Echec de la creation d'un serveur tcp");
			return;
		}
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
			// echo
			channel->write(buf);
		};
		srv.setThreadNum(4);
		srv.start();
	}
}