#pragma once

#include <string>
#include <unordered_map>
#include "httprequest.h"

struct HttpResponse {
  std::unordered_map<std::string, std::string> statusLine;
  std::unordered_map<std::string, std::string> headers;
  std::string body;

  std::string stringify();
};
