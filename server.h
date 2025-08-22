#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

class Server {
private:
  addrinfo* servInfo;
  int sockFd;
  sockaddr clientInfo;
  int clientFd;
  char message[];

public:
  ~Server();
  void getServerAddrInfo(int ai_family, int ai_socktype);
  void makeSocket();
  void bindSocket();
  void listenSocket();
  void acceptConn();
  void getHttpRequest();
  void sendHttpResponse();
};
