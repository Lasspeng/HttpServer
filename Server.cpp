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
  int addrInfo = getaddrinfo("127.0.0.1", "8080", &hints, &servInfo);

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

  while (true) {
    // Get message from TCP client
    void* incMsg = malloc(100);
    int recBytes = recv(clientSockFd, incMsg, 100, 0);
    if (recBytes == -1) {
      std::cerr << "Could not retrieve message\n";
    } else if (recBytes == 0) {
      std::cout << "Client has closed the TCP connection\n";
    }
    char* incMsgStr = (char*)incMsg;
    std::cout << incMsgStr << '\n';

          
    int len = strlen(incMsgStr);
    for (int i = 0; i < len; i++) {
      incMsgStr[i] = std::toupper(incMsgStr[i]);
    }

    // Send message back to client
    int sentBytes = send(clientSockFd, incMsgStr, len, 0);
    if (sentBytes == -1) {
      std::cerr << "Message could not be sent over the TCP connection\n";
    }
    free(incMsg);
  }

  // close(clientSockFd);
  close(sockFd);
  freeaddrinfo(servInfo);
  return 0;
}
