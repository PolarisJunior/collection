#pragma once
#include <thread>

class Server {
  std::thread th;

 public:
  void launchServer();

  void finish();
};
