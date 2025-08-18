#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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

  // Bind socket to port
  int bindN = bind(sockFd, servInfo->ai_addr, servInfo->ai_addrlen);
  if (bindN == -1) {
    std::cerr << "Socket could not be bound\n";
  }


  freeaddrinfo(servInfo);
  return 0;
}
