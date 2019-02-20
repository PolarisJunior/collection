
#include "../HttpService.h"
#include <WinSock2.h>
#include <Windows.h>
#include "../Socket.h"

HttpService::HttpService() {}

HttpService::~HttpService() {}

void HttpService::requestGet() {
  if (!Socket::isInitialized()) {
    Socket::initSocketSystem();
  }
}