#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main() {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo* servInfo;
  int addrInfo = getaddrinfo(NULL, "3490", &hints, &servInfo);

  // Create socket
  int sockFd = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol);
  if (sockFd == -1) {
    std::cerr << "Socket could not be created\n";
  }

  // Bind socket to ip address and port number
  int bindN = bind(sockFd, servInfo->ai_addr, servInfo->ai_addrlen);
  if (bindN == -1) {
    std::cerr << "Socket could not be bound\n";
  }

  // Have socket listen for incoming TCP connection requests
  int listenN = listen(sockFd, 5);
  if (listenN == -1) {
    std::cerr << "Socket could not listen for connections\n";
  }

  // Accept incoming TCP connection
  struct sockaddr clientInfo;
  socklen_t size = sizeof(clientInfo);
  int clientSockFd = accept(sockFd, &clientInfo, &size);
  if (clientSockFd == -1) {
    std::cerr << "Connection with incoming TCP request could not be made\n";
  }


  close(clientSockFd);
  close(sockFd);
  freeaddrinfo(servInfo);
  return 0;
}
