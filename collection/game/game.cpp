
#include <SDL.h>
#include <iostream>

#include "../datastructures/Trie.h"
#include "../misc/arrayHopper.h"

#include "../ui/Input.h"
#include "../ui/SdlEventPoller.h"
#include "../ui/Window.h"
#include "../ui/WindowBuilder.h"
#include "../util/time/Time.h"

#include "../game/Actor.h"
#include "../game/Camera2.h"
#include "../game/Component.h"
#include "../game/RenderComponent.h"
#include "../game/RenderSystem.h"
#include "../graphics/Color.h"
#include "../graphics/Renderer.h"
#include "../math/geometry/Rect.h"
#include "../util/EventScheduler.h"

static bool running;
static SdlEventPoller eventPoller;

static const uint32_t UPDATE_FREQUENCY = 60;
static const uint32_t UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;
static const uint32_t MAX_LOOPS = 10;

Camera2 mainCamera;
EventScheduler eventScheduler;
Renderer mainRenderer;

int main(int argc, char** argv) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
  }

  WindowBuilder windowBuilder;
  windowBuilder.setTitle("Game").setDims(800, 600);
  Window* window = windowBuilder.getWindow();
  mainRenderer = window->getRenderer();

  eventPoller.addListener(SDL_QUIT,
                          [](const SDL_Event& event) { running = false; });

  Actor actor;
  Component component;
  RenderComponent renderComp;
  actor.attachComponent(&renderComp);
  // actor.attachComponent(&component);

  eventScheduler.scheduleEvent(
      []() { std::cout << "scheduled event ran" << std::endl; }, 3.0);
  Rect rect = {0, 0, 50, 50};

  /* Main Game Loop */
  running = true;
  uint32_t lastUpdate = Time::getMs();
  while (running) {
    uint32_t currentMs = Time::getMs();
    uint32_t frameTime = 0;
    uint32_t numLoops = 0;

    while ((currentMs - lastUpdate) > UPDATE_PERIOD && numLoops < MAX_LOOPS) {
      eventScheduler.runUpTo(lastUpdate);

      lastUpdate += UPDATE_PERIOD;
      frameTime += UPDATE_PERIOD;
      numLoops++;
    }
    eventPoller.pollEvents();

    float interpolation =
        fmin(1.f, static_cast<float>(currentMs - lastUpdate) / UPDATE_PERIOD);

    mainRenderer.setColor(Colors::BLACK);
    mainRenderer.clear();
    renderSystem.renderAll(interpolation);
    mainRenderer.setColor(Colors::WHITE);
    mainRenderer.drawRect(rect);
    mainRenderer.present();
  }

  return EXIT_SUCCESS;
}