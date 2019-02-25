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

Socket::~Socket() {
  if (socketId != INVALID_SOCKET) {
    closesocket(socketId);
  }
}

std::string Socket::receive() {
  static constexpr int32_t BUF_SIZE = 4096;
  int32_t res;
  char buf[BUF_SIZE + 1];
  std::stringstream ss;

  do {
    printf("about to recv %x %x\n", socketId, buf);
    res = recv(this->socketId, buf, BUF_SIZE - 1, 0);
    printf("recvd\n");
    if (res > 0) {
      printf("%d bytes received\n", res);
      buf[res] = '\0';
      ss << buf;
    } else if (res == 0) {
      printf("Connection closed\n");
    } else if (res == WSAETIMEDOUT) {
    } else {
      printf("recv failed: %d\n", WSAGetLastError());
    }
    printf("real res%d\n", res);
  } while (res > 0);

  return ss.str();
}

void Socket::sendMsg(const char* msg, int32_t msgLen) {
  int32_t res;
  res = send(socketId, msg, msgLen, 0);
}

int32_t Socket::initSocketSystem() {
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

void Socket::setSendTimeout(int32_t to) {
  int32_t r =
      setsockopt(socketId, SOL_SOCKET, SO_SNDTIMEO, (char*)&to, sizeof(to));
}

void Socket::setRecvTimeout(int32_t to) {
  int32_t r =
      setsockopt(socketId, SOL_SOCKET, SO_RCVTIMEO, (char*)&to, sizeof(to));
}

int32_t Socket::endSocketSystem() {
  int32_t res = WSACleanup();
  Socket::initialized = false;
  return res;
}