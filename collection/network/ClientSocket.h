
#pragma once

#include "Socket.h"

class ClientSocket : public Socket {
 public:
  ClientSocket();
  ~ClientSocket() = default;
};