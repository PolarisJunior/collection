#include "../Socket.h"

#include <WinSock2.h>
#include <cstdio>

bool Socket::initialized = false;

Socket::Socket() : Socket(INVALID_SOCKET) {}

Socket::Socket(SocketId socketId) {
  if (!isInitialized()) {
    initSocketSystem();
  }
  this->socketId = socketId;
}

Socket::~Socket() {
  if (socketId != INVALID_SOCKET) {
    closesocket(socketId);
  }
}

int32_t Socket::initSocketSystem() {
  printf("Initializing socket system\n");

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