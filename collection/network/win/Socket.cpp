#include "../Socket.h"

#include <WinSock2.h>
#include <cstdio>

int32_t Socket::initSocketSystem() {
  WSADATA wsaData;
  int32_t res = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (res != 0) {
    printf("Winsock startup failed, %d\n", res);
  }
  printf("version%d\n", wsaData.wVersion);
  printf("yes%s::%s\n", wsaData.szDescription, wsaData.szSystemStatus);

  return res;
}