
#pragma once

#include <cstdint>

typedef uint64_t SOCKET;

class ServerSocket {
 public:
  ServerSocket();
  ~ServerSocket();

 private:
  SOCKET listenSocket;
};