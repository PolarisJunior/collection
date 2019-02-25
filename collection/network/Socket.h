#pragma once
#include <chrono>
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
  void setSendTimeout(std::chrono::milliseconds ms);
  void setRecvTimeout(std::chrono::milliseconds ms);
  void setSendTimeout(std::chrono::seconds s);
  void setRecvTimeout(std::chrono::seconds s);

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

inline void Socket::setSendTimeout(std::chrono::milliseconds ms) {
  setSendTimeout(ms.count());
}

inline void Socket::setRecvTimeout(std::chrono::milliseconds ms) {
  setRecvTimeout(ms.count());
}

inline void Socket::setSendTimeout(std::chrono::seconds s) {
  setSendTimeout(std::chrono::duration_cast<std::chrono::milliseconds>(s));
}

inline void Socket::setRecvTimeout(std::chrono::seconds s) {
  setRecvTimeout(std::chrono::duration_cast<std::chrono::milliseconds>(s));
}