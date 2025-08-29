#pragma once

#include "httprequest.h"
#include <functional>
#include <string>

namespace Router {

// Hash function for route keys
struct PairHash {
  std::size_t operator()(const std::pair<std::string, std::string>& pair) const noexcept;
};

using Handler = std::function<std::string(const HttpRequest*)>;
// Declare the route map
extern std::unordered_map<std::pair<std::string, std::string>,
                          Handler,
                          PairHash> routes;
// Populate the route map
void makeRoutes();
std::string dispatch(const std::string& method, const std::string& path, const HttpRequest* req);
}
