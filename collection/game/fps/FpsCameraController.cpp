
#include "FpsCameraController.h"
#include <iostream>
#include "ui/Input.h"
#include "ui/Mouse.h"

void FpsCameraController::update(float deltaTime) {
  if (Mouse::left()) {
    std::cout << "foo" << std::endl;
  }
  // Input::g
}