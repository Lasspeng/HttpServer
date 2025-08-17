#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>

int main() {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  const char* domain = "google.com";
  const char* port = "80";

  struct addrinfo* res;
  int addrInfo = getaddrinfo(domain, port, &hints, &res);
  if (addrInfo != 0) {
    std::cerr << "Could not get any address info\n";
  }

  int sockFd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockFd == -1) {
    std::cerr << "socket() has failed\n";
  }


  return 0;
}
