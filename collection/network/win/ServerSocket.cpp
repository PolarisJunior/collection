
#include "../ServerSocket.h"
#include "../Socket.h"

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <cstdio>
#include <cstring>

const char* LOCAL_HOST = "127.0.0.1";

// add Ws2_32.lib in visual studio
// #pragma comment(lib, "Ws2_32.lib")
ServerSocket::ServerSocket() {
  struct addrinfo *result = NULL, hints;
  ZeroMemory(&hints, sizeof(hints));
  int32_t r = getaddrinfo(LOCAL_HOST, "27015", &hints, &result);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;
  // hints.ai_protocol = IPPROTO_TCP;
  // hints.ai_flags = 0;

  if (r != 0) {
    printf("getaddrinfo failed\n");
    // WSACleanup();
    return;
  }

  socketId = INVALID_SOCKET;

  socketId =
      socket(result->ai_family, result->ai_socktype, result->ai_protocol);

  if (socketId == INVALID_SOCKET) {
    printf("error creating listensocket\n");
    freeaddrinfo(result);
    // WSACleanup();
    return;
  }

  r = bind(socketId, result->ai_addr, (int32_t)result->ai_addrlen);
  if (r == SOCKET_ERROR) {
    printf("bind failed with error: %d\n", WSAGetLastError());
    freeaddrinfo(result);
    closesocket(socketId);
    // WSACleanup();
    return;
  }

  freeaddrinfo(result);

  if (listen(socketId, SOMAXCONN) == SOCKET_ERROR) {
    printf("listen failed %ld\n", WSAGetLastError());
    closesocket(socketId);
    // WSACleanup();
    return;
  }
  valid = true;
}

ServerSocket::~ServerSocket() {
  WSACleanup();
}

std::unique_ptr<Socket> ServerSocket::acceptConnection() {
  printf("waiting for client connection\n");
  SOCKET clientSocket = INVALID_SOCKET;

  clientSocket = accept(socketId, nullptr, nullptr);

  if (clientSocket == INVALID_SOCKET) {
    printf("accept socket failed: %d\n", WSAGetLastError());
    closesocket(socketId);
    WSACleanup();
  }
  printf("client connected\n");
  return std::make_unique<Socket>(clientSocket);
}