#pragma once

#include <unordered_map>
#include <string>

class HttpRequest {
public:
  HttpRequest();
  std::string rawRequest;
  std::unordered_map<std::string, std::string> requestLine;
  std::unordered_map<std::string, std::string> headers;
  std::string body;

  void parseRawRequest();
};
