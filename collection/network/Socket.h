#pragma once
#include <cstdint>
#include <memory>
#include <string>

typedef uint64_t SocketId;

class Socket {
 public:
  Socket();
  Socket(SocketId socketId);
  ~Socket();

  SocketId getSocketId();

  std::string receive();
  void sendMsg(const std::string& msg);
  void sendMsg(const char* msg, int32_t msgLength);

  /* sets timeout in ms */
  void setSendTimeout(int32_t to);
  void setRecvTimeout(int32_t to);

  bool isValid();

  static int32_t initSocketSystem();
  static int32_t endSocketSystem();
  static bool isInitialized();

 protected:
  static bool initialized;
  SocketId socketId;
  bool valid;
};

inline bool Socket::isInitialized() {
  return Socket::initialized;
}

inline SocketId Socket::getSocketId() {
  return socketId;
}

inline void Socket::sendMsg(const std::string& msg) {
  sendMsg(msg.c_str(), msg.length());
}

inline bool Socket::isValid() {
  return valid;
}