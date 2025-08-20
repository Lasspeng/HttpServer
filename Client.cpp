#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
  // Give some server info
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  const char* domain = "google.com";
  const char* service = "http";

  // Get address info for server
  struct addrinfo* servInfo;
  int addrInfo = getaddrinfo(domain, service, &hints, &servInfo);
  if (addrInfo != 0) {
    std::cerr << "Could not get any address info\n";
  }

  // Create client socket
  int sockFd = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol);
  if (sockFd == -1) {
    std::cerr << "Socket could not be created\n";
  }
  // Print IP address and port
  struct sockaddr_in* ipv4 = (struct sockaddr_in*)servInfo->ai_addr;
  char ipstr[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(ipv4->sin_addr), ipstr, sizeof(ipstr));
  int port = ntohs(ipv4->sin_port);
  std::cout << "IP: " << ipstr << " Port: " << port << '\n';

  // Connect to server socket
  int conn = connect(sockFd, servInfo->ai_addr, servInfo->ai_addrlen);
  if (conn == -1) {
    std::cerr << "Connection could not be made\n";
  }


  freeaddrinfo(servInfo);
  return 0;
}
