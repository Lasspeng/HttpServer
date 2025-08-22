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

public:
  Server() = default;

  void makeSocket(int ai_family, int ai_socktype) {
    sockFd = socket(ai_family, ai_socktype, 0);
    if (sockFd == -1) {
      std::cerr << "Socket could not be created\n";
    }
  }

  void bindSocket() {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(8080);
    addr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    int bindStatus = bind(sockFd, (sockaddr*)&addr, sizeof(addr));
    if (bindStatus == -1) {
      std::cerr << "Socket could not be bound\n";
    }
  }

  void listenSocket() {
    int listenStatus = listen(sockFd, 5);
    if (listenStatus == -1) {
      std::cerr << "Socket could not listen for connections\n";
    }
  }

  void acceptConn() {
    socklen_t size = sizeof(clientInfo);
    clientFd = accept(sockFd, &clientInfo, &size);
    if (clientFd == -1) {
    std::cerr << "Connection with incoming TCP request could not be made\n";
    }
  }

  void getMessage() {
    char msg[100];
    int recvBytes = recv(clientFd, &msg, 100, 0);
    if (recvBytes == 0) {
      std::cerr << "Could not retrieve message\n";
    }
  }

};
