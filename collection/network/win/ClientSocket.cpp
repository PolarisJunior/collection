
#include "../ClientSocket.h"

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <cstdint>
#include <cstdio>

ClientSocket::ClientSocket() {
  struct addrinfo *result = NULL, *ptr = NULL, hints;

  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;

  int32_t iResult = getaddrinfo("127.0.0.1", "27015", &hints, &result);
  if (iResult != 0) {
    printf("getaddrinfo failed: %d\n", iResult);
    WSACleanup();
  }

  // SOCKET connectSocket = INVALID_SOCKET;
  socketId = INVALID_SOCKET;

  ptr = result;
  socketId = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

  if (socketId == INVALID_SOCKET) {
    printf("error connect socket\n");
    freeaddrinfo(result);
    WSACleanup();
  }

  iResult = connect(socketId, ptr->ai_addr, (int)ptr->ai_addrlen);
  if (iResult == SOCKET_ERROR) {
    closesocket(socketId);
    socketId = INVALID_SOCKET;
  }

  freeaddrinfo(result);

  if (socketId == INVALID_SOCKET) {
    printf("unable to connect\n");
    WSACleanup();
  }
}