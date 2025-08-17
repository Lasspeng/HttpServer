#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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
  struct addrinfo* res;
  int addrInfo = getaddrinfo(domain, service, &hints, &res);
  if (addrInfo != 0) {
    std::cerr << "Could not get any address info\n";
  }

  // Create socket
  int sockFd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockFd == -1) {
    std::cerr << "Socket could not be created\n";
  }

  // Bind socket to port
  // int bindN = bind(sockFd, res->ai_addr, res->ai_addrlen);
  // if (bindN == -1) {
  //   std::cerr << "Socket could not be bound\n";
  // }

  // Connect to socket
  int conn = connect(sockFd, res->ai_addr, res->ai_addrlen);
  if (conn == -1) {
    std::cerr << "Connection could not be made\n";
  }

  freeaddrinfo(res);
  return 0;
}
