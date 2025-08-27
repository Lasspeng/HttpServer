#include <unordered_map>
#include <string>
#include <functional>
#include "httprequest.h"
#include "httpresponse.h"

namespace Router {

struct PairHash {
  std::size_t operator() (const std::pair<std::string, std::string>& pair) const noexcept {
    std::size_t h1 = std::hash<std::string>{}(pair.first);
    std::size_t h2 = std::hash<std::string>{}(pair.second);
    return h1 ^ (h2 << 1);
  }
};

using Handler = std::function<std::string(const HttpRequest*)>;

std::unordered_map<std::pair<std::string, std::string>, Handler, PairHash> routes;

void makeRoutes() {
  routes[{"GET", "/"}] = [](const HttpRequest* req) {
    HttpResponse response;
    response.statusLine["status-code"] = "200";
    response.statusLine["status-text"] = "OK";
    response.statusLine["protocol"] = req->requestLine.at("version");
    return response.stringify();
  };
}



}
