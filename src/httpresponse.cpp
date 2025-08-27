#include "httpresponse.h"

std::string HttpResponse::stringify() {
  std::string response = "";

  response += statusLine["protocol"];
  response += std::string(" ") += statusLine["status-code"];
  response += std::string(" ") += statusLine["status-text"];
  response += "\r\n";

  for (const auto& pair : headers) {
    response += pair.first;
    response += ": ";
    response += pair.second;
    response += "\r\n";
  }

  response += "\r\n";
  response += body;

  return response;
}
