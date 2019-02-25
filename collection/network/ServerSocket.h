
#pragma once

#include <cstdint>
#include <memory>
#include "Socket.h"

class ServerSocket : public Socket {
 public:
  ServerSocket();
  ~ServerSocket();

  std::unique_ptr<Socket> acceptConnection();

 private:
  bool valid;
};
