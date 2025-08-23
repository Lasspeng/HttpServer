#pragma once

#include <unordered_map>
#include <string>

class HttpRequest {
public:
  std::string rawRequest;
  std::unordered_map<std::string, std::string> requestLine;
  std::unordered_map<std::string, std::string> headers;
  std::string body;



};
