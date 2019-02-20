#pragma once
#include <cstdint>

typedef uint64_t SocketId;

class Socket {
 public:
  Socket();
  Socket(SocketId socketId);
  ~Socket();

  SocketId getSocketId();

  static int32_t initSocketSystem();
  static int32_t endSocketSystem();
  static bool isInitialized();

 protected:
  static bool initialized;
  SocketId socketId;
};

inline bool Socket::isInitialized() {
  return Socket::initialized;
}

inline SocketId Socket::getSocketId() {
  return socketId;
}