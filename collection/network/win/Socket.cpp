#include "../Socket.h"

#include <WinSock2.h>
#include <cstdio>
#include <sstream>

bool Socket::initialized = false;

Socket::Socket() : Socket(INVALID_SOCKET) {}

Socket::Socket(SocketId socketId) {
  if (!isInitialized()) {
    initSocketSystem();
  }
  this->socketId = socketId;
}

std::string Socket::receive() {
  static constexpr int32_t BUF_SIZE = 4096;
  int32_t res;
  char buf[BUF_SIZE + 1];
  std::stringstream ss;

  do {
    res = recv(this->socketId, buf, BUF_SIZE, 0);
    if (res > 0) {
      printf("%d bytes received\n", res);
      buf[res] = '\0';
      ss << buf;
    } else if (res == 0) {
      printf("Connection closed\n");
    } else {
      printf("recv failed: %s\n", WSAGetLastError());
    }
  } while (res > 0);

  return ss.str();
}

void Socket::sendMsg(const char* msg, int32_t msgLen) {
  int32_t res;
  res = send(socketId, msg, msgLen, 0);
  printf("packets sent %d\n", res);
}

Socket::~Socket() {
  if (socketId != INVALID_SOCKET) {
    closesocket(socketId);
  }
}

int32_t Socket::initSocketSystem() {
  // printf("Initializing socket system\n");

  WSADATA wsaData;
  int32_t res = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (res != 0) {
    printf("Winsock startup failed, %d\n", res);
    return res;
  }
  // printf("winsock version %d\n", wsaData.wVersion);
  // printf("%s :: %s\n", wsaData.szDescription, wsaData.szSystemStatus);
  Socket::initialized = true;
  return res;
}

int32_t Socket::endSocketSystem() {
  int32_t res = WSACleanup();
  Socket::initialized = false;
  return res;
}