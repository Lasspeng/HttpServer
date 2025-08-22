#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "server.h"


int main() {
  Server server;
  server.getServerAddrInfo(AF_INET, SOCK_STREAM);
  server.makeSocket();
  server.bindSocket();
  server.listenSocket();

  while (true) {
    server.acceptConn();
    // server.handleRequest();
    server.getHttpRequest();
    server.sendHttpResponse();
  }

  return 0;
}
