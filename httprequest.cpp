#include "httprequest.h"
#include <iostream>
#include <string>

HttpRequest::HttpRequest() : body("") {};

void HttpRequest::parseRawRequest() {
  // Isolate request line
  size_t lineEnd = rawRequest.find("\r\n");
  if (lineEnd == std::string::npos) {
    std::cerr << "Bad Request: CRLF after request line is missing\n";
  }

  // Get indices of request line fields
  size_t methodIdx = 0;
  size_t targetIdx = rawRequest.find(' ');
  size_t versionIdx = rawRequest.find(' ', targetIdx + 1);
  if (targetIdx == std::string::npos || 
      versionIdx == std::string::npos) {
    std::cerr << "Bad Request: Incorrect formatting in request line\n";
  }

  requestLine["method"] = rawRequest.substr(0, targetIdx);
  requestLine["target"] = rawRequest.substr(targetIdx + 1, versionIdx - targetIdx - 1);
  requestLine["version"] = rawRequest.substr(versionIdx + 1, lineEnd - versionIdx - 1);

  // Get header fields
  size_t headersEnd = rawRequest.find("\r\n\r\n");
  size_t headersStart = lineEnd + 2;
  size_t curr = headersStart;

// Add each header key and value to hashmap
  while (curr < headersEnd) {
    size_t keyEnd = rawRequest.find(':', curr);
    size_t valueEnd = rawRequest.find("\r\n", curr);
    if (keyEnd == std::string::npos ||
        valueEnd == std::string::npos) {
      std::cerr << "No colon in header line\n";
    }

    std::string key = rawRequest.substr(curr, keyEnd - curr);
    std::string value = rawRequest.substr(keyEnd + 2, valueEnd - (keyEnd + 2));

    headers.emplace(std::move(key), std::move(value));
    curr = valueEnd + 2;
  }

  // Get request body (if there is any)
  if (headers.find("Content-Length") == headers.end()) return;
  curr = headersEnd + 4;
  body = rawRequest.substr(curr, std::stoi(headers["Content-Length"]));
}
