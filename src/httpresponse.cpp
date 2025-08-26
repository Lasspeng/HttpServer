#include "httpresponse.h"

std::string HttpResponse::stringify() {
  std::string response = "";

  response += statusLine["protocol"];
  response += std::string(" ") += statusLine["status-code"];
  response += std::string(" ") += statusLine["status-text"];
  response += "\n";

  for (std::pair& pair : req) {
    response += 
  }

  return response;
}
