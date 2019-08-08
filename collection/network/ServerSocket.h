
#pragma once

#include <cstdint>
#include <memory>
#include "Socket.h"

class ServerSocket : public Socket {
 public:
  ServerSocket(int32_t port);
  ~ServerSocket();

  std::unique_ptr<Socket> acceptConnection();

 private:
  bool valid;
};
