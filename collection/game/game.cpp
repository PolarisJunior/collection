
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <memory>

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
#include "../graphics/Image.h"
#include "../graphics/Renderer.h"
#include "../graphics/Texture.h"

#include "../math/geometry/Rect.h"
#include "../util/EventScheduler.h"

#include "../io/File.h"

static bool running;
static SdlEventPoller eventPoller;

static const uint32_t UPDATE_FREQUENCY = 60;
static const uint32_t UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;
static const uint32_t MAX_LOOPS = 10;

static Actor actor;

Camera2 mainCamera;
EventScheduler eventScheduler;
Renderer mainRenderer;

int main(int argc, char** argv) {
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
  }
  {
    uint32_t flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if (IMG_Init(flags) != flags) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, IMG_GetError());
    }
  }

  WindowBuilder windowBuilder;
  windowBuilder.setTitle("Game").setDims(800, 600).setVisible();

  std::unique_ptr<Window> window =
      std::unique_ptr<Window>(windowBuilder.getWindow());

  mainRenderer = window->getRenderer();

  {
    // SDL_Surface* surface = IMG_Load("../res/monkey.png");
    // SDL_Texture* tex =
    //     SDL_CreateTextureFromSurface(mainRenderer.sdlRenderer, surface);
    // SDL_RenderCopy(mainRenderer.sdlRenderer, tex, nullptr, nullptr);
    // SDL_RenderPresent(mainRenderer.sdlRenderer);
    Image image("../res/monkey.png");
    std::cout << "extension: " << image.getType() << std::endl;
    Texture texture(image);
    mainRenderer.render(texture);
    mainRenderer.present();
    SDL_Delay(3000);
  }

  eventPoller.addListener(SDL_QUIT,
                          [](const SDL_Event& event) { running = false; });
  mainCamera.width = window->getWidth();
  mainCamera.height = window->getHeight();

  actor.x = 0;
  actor.y = 0;
  mainCamera.moveCamera(-10, -10);
  Component component;
  RenderComponent renderComp;
  actor.attachComponent(&renderComp);

  eventPoller.addListener(SDL_KEYDOWN, [](const SDL_Event& event) {
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        actor.y += -1;
        break;
      case SDLK_RIGHT:
        actor.x += 1;
        break;
      case SDLK_DOWN:
        actor.y += 1;
        break;
      case SDLK_LEFT:
        actor.x -= 1;
        break;
    }
  });

  eventPoller.addListener(SDL_MOUSEBUTTONDOWN, [](const SDL_Event& event) {
    Vector2 worldPos =
        mainCamera.toWorldCoords(Vector2(event.button.x, event.button.y));
    printf("screen coords: (%d, %d), world coords: (%.3f, %.3f)\n",
           event.button.x, event.button.y, worldPos.x, worldPos.y);
  });

  eventScheduler.scheduleEvent(
      []() { std::cout << "scheduled event ran" << std::endl; }, 3.0);
  Rect rect = {0, 0, 50, 50};

  File file("../res/data.txt");
  std::cout << "exists " << file.exists() << std::endl;
  std::cout << "file size " << file.getSize() << std::endl;
  auto bytes = file.readBytes();
  for (int32_t i = 0; i < file.getSize(); i++) {
    std::cout << "byte:" << bytes[i] << "\n";
  }
  Image image("../res/monkey.png");
  std::cout << "image size: " << image.getImageSize() << std::endl;

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