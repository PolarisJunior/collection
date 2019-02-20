
#pragma once

#include <cstdint>
#include <memory>
#include "Socket.h"

class ServerSocket : public Socket {
 public:
  ServerSocket();
  ~ServerSocket();

  std::unique_ptr<Socket> acceptConnection();

  bool isValid();

 private:
  // uint64_t socketId;
  bool valid;
};

inline bool ServerSocket::isValid() {
  return valid;
}