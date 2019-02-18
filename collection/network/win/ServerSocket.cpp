
#include "../ServerSocket.h"

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <cstdio>
#include <cstring>

// add Ws2_32.lib in visual studio
// #pragma comment(lib, "Ws2_32.lib")
ServerSocket::ServerSocket() {
  struct addrinfo* result = nullptr;
  struct addrinfo hints;

  memset(&hints, 0, sizeof(hints));
  int32_t r = getaddrinfo(nullptr, "27015", &hints, &result);

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  if (r != 0) {
    printf("getaddrinfo failed\n");
    WSACleanup();
  }

  SOCKET listenSocket = INVALID_SOCKET;

  listenSocket =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);

  if (listenSocket == INVALID_SOCKET) {
    printf("error creating listensocket\n");
    freeaddrinfo(result);
    WSACleanup();
  }

  r = bind(listenSocket, result->ai_addr, (int32_t)result->ai_addrlen);
  if (r == SOCKET_ERROR) {
    printf("bind failed with error: %d\n", WSAGetLastError());
    freeaddrinfo(result);
    closesocket(listenSocket);
    WSACleanup();
  }

  freeaddrinfo(result);

  if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
    printf("listen failed %ld\n", WSAGetLastError());
    closesocket(listenSocket);
    WSACleanup();
  }

  SOCKET clientSocket = INVALID_SOCKET;
  printf("waiting for client connection\n");

  clientSocket = accept(listenSocket, nullptr, nullptr);
  if (clientSocket == INVALID_SOCKET) {
    printf("accept socket failed: %d\n", WSAGetLastError());
    closesocket(listenSocket);
    WSACleanup();
  }
  printf("client connected\n");
}