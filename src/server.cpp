#include "server.h"
#include "httprequest.h"
#include "router.h"


Server::~Server() {
  freeaddrinfo(servInfo);
  delete request;
  close(sockFd);
}

void Server::getServerAddrInfo(int ai_family, int ai_socktype) {
  addrinfo hints{};
  hints.ai_family = ai_family;
  hints.ai_socktype = ai_socktype;
  hints.ai_flags = AI_PASSIVE;

  int addrInfoStatus = getaddrinfo("127.0.0.1", "8080", &hints, &servInfo);
  if (addrInfoStatus != 0) {
    std::cerr << "Could not get address info for server\n";
  }
}

void Server::makeSocket() {
  sockFd = socket(servInfo->ai_family, servInfo->ai_socktype, servInfo->ai_protocol);
  if (sockFd == -1) {
    std::cerr << "Socket could not be created\n";
  }
}

void Server::bindSocket() {
  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

  int bindStatus = bind(sockFd, servInfo->ai_addr, servInfo->ai_addrlen);
  if (bindStatus == -1) {
    std::cerr << "Socket could not be bound\n";
  }
}

void Server::listenSocket() {
  int listenStatus = listen(sockFd, 5);
  if (listenStatus == -1) {
    std::cerr << "Socket could not listen for connections\n";
  }
}

void Server::acceptConn() {
  socklen_t size = sizeof(clientInfo);
  clientFd = accept(sockFd, &clientInfo, &size);
  if (clientFd == -1) {
  std::cerr << "Connection with incoming TCP request could not be made\n";
  }
}

void Server::getHttpRequest() {
  char buf[4096];
  request = new HttpRequest();
  int recvBytes = recv(clientFd, buf, sizeof(buf), 0);

  if (recvBytes == -1) {
    std::cout << "Peer has closed connection\n";
    close(clientFd);
  } else if (recvBytes > 0) {
    request->rawRequest.append(buf, recvBytes);
  }
  request->parseRawRequest();
}

void Server::sendHttpResponse() {
  for (auto pair : request->requestLine) {
    std::cout << pair.first << ": " << pair.second << '$' << '\n';
  }
  std::cout << '\n';
  for (auto pair: request->headers) {
    std::cout << pair.first << ": " << pair.second << '\n';
  }
  std::cout << '\n';
  std::cout << "Body: " << request->body << '\n';


  // std::string body = "Greetings from the HTTP server\n";
  // std::string bodylen = std::to_string(body.size());
  // std::string response = "";
  // response += "HTTP/1.1 200 OK\r\n";
  // response += "Content-Type: text/html\r\n";
  // response += "Content-Length: " + bodylen + "\r\n";
  // response += "Connection: close\r\n";
  // response += "\r\n";
  // response += body;
  std::string reqMethod = request->requestLine["method"];
  std::string reqPath = request->requestLine["target"];
  std::string response = Router::routes[{reqMethod, reqPath}](request);

  // Send message back to the client
  int sendStatus = send(clientFd, response.data(), response.size(), 0);
  if (sendStatus == -1) {
    std::cerr << "Message could not be sent over the TCP connection\n";
  }
  std::cout << "Sent response\n";
}

// void Server::handleRequest() {
//   while (true) {
//     getHttpRequest();
//     sendHttpResponse();
//   }
// }
