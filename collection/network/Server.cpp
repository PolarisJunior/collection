
#include "Server.h"
#include "game/GameInstance.h"
#include "network/ServerSocket.h"

#include <iostream>
#include <thread>

void printLoop() {
  int32_t c = 0;
  while (GameInstance::isRunning && c < 100) {
    std::cout << "Counter:" << c << std::endl;
    c++;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void ServerMain() {
  ServerSocket socket(27015);
  std::unique_ptr<Socket> sock = socket.acceptConnection();
  std::string myMsg = "frappucino";
  sock->sendMsg(myMsg);
}

void Server::launchServer() {
  th = std::thread(ServerMain);
  th.detach();
}

void Server::finish() {
  // th.join();
}