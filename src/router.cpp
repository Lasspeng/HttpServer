#include "router.h"
#include <unordered_map>
#include "httpresponse.h"

namespace Router {

// Create hashing function for route map
std::size_t PairHash::operator() (const std::pair<std::string, std::string>& pair) const noexcept {
  std::size_t h1 = std::hash<std::string>{}(pair.first);
  std::size_t h2 = std::hash<std::string>{}(pair.second);
  return h1 ^ (h2 << 1);
}

// Create route map that takes in an http method and path/target key pair that maps to a function that generates an http response
std::unordered_map<std::pair<std::string, std::string>,
                   Handler,
                   PairHash> routes;

// This function will populate the route map for my http server's responses
void makeRoutes() {
  routes[{"GET", "/"}] = [](const HttpRequest* req) {
    HttpResponse response;
    response.statusLine["status-code"] = "200";
    response.statusLine["status-text"] = "OK";
    response.statusLine["protocol"] = req->requestLine.at("version");

    if (req->headers.at("Connection") == "close") {
      response.statusLine["Connection"] = "close";
    }
    response.statusLine["Content-Type"] = "text/html";
    std::string body = "Greetings from the HTTP server\n";
    std::size_t strlen = body.size();
    response.headers["Content-Length"] = std::to_string(strlen);

    response.body = body;
    return response.stringify();
  };
}



}
