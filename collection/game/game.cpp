
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
#include "../game/Stage.h"
#include "../game/ecs/EntityManager.h"
#include "../game/ecs/PositionManager.h"
#include "../game/ecs/SpriteManager.h"

#include "../graphics/Color.h"
#include "../graphics/Image.h"
#include "../graphics/Renderer.h"
#include "../graphics/Sprite.h"
#include "../graphics/Texture.h"
#include "../graphics/TileMap.h"
#include "../graphics/TileSet.h"

#include "../math/geometry/Rect.h"
#include "../util/EventScheduler.h"

#include "../io/File.h"

#include "../network/ClientSocket.h"
#include "../network/ServerSocket.h"
#include "../network/Socket.h"

#include "../sys/System.h"

#include "../math/Vector3.h"

#include "../database/RelationalDatabase.h"
#include "../io/FileInputStream.h"

static bool running;
static SdlEventPoller eventPoller;

static const uint32_t UPDATE_FREQUENCY = 60;
static const uint32_t UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;
static const uint32_t MAX_LOOPS = 10;

static Actor actor;

Camera2 mainCamera;
EventScheduler eventScheduler;
Renderer mainRenderer;
Window mainWindow;

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

  // std::optional<RelationalDatabase> db =
  //   RelationalDatabase::loadDatabase("test2.db");
  // if (db) {
  //   printf("create\n");
  //   db->createTable();
  // } else {
  //   printf("not create\n");
  // }

  // ClientSocket clientSocket;
  // clientSocket.setRecvTimeout(std::chrono::seconds(5));
  // std::string str = clientSocket.receive();

  // std::cout << "received: " << str << std::endl;

  // std::string ourMsg = "hello network";
  // clientSocket.sendMsg(ourMsg);

  // ServerSocket socket;
  // std::unique_ptr<Socket> sock = socket.acceptConnection();
  // std::string myMsg = "frappucino";
  // sock->sendMsg(myMsg);

  WindowBuilder windowBuilder;
  windowBuilder.setTitle("Game").setDims(800, 600).setVisible();

  mainWindow = windowBuilder.getWindow();
  mainRenderer = Renderer(mainWindow);

  TileSet tileSet("../res/medieval_tilesheet.png", 64, 64, 32, 32, 32, 32);
  TileSet rogueSet("../res/roguelikeSheet_transparent.png", 15, 15, 2, 2, 0, 0,
                   0, 0);
  std::optional<TileMap> rogueMap =
      TileMap::loadMapFromCsv("../res/rogue_map.csv");
  if (rogueMap) {
    std::cout << "rogue map exists" << std::endl;
    rogueMap->setTileSet(rogueSet);
  }

  Stage stage;
  stage.setTileMap(*rogueMap);
  stage.setMapOffset({10, 10});

  eventPoller.addListener(SDL_QUIT,
                          [](const SDL_Event& event) { running = false; });

  mainCamera.setWidth(static_cast<float>(mainWindow.getWidth()));
  mainCamera.setHeight(static_cast<float>(mainWindow.getHeight()));

  actor.x = 0;
  actor.y = 0;
  mainCamera.moveCamera(0, 0);
  mainCamera.attachToActor(&actor);
  mainCamera.setAttachOffset(Vector2(100.0f, 100.0f));

  RenderComponent renderComp;
  Sprite playerSprite("../res/monkey.png");
  actor.attachComponent(renderComp);
  actor.attachComponent(playerSprite);

  Actor actor2;
  actor2.x = -50;
  actor2.y = -50;
  RenderComponent renderComp2;
  actor2.attachComponent(&renderComp2);

  EntityManager manager(256);
  std::cout << "alive? idx 0 " << manager.isAlive(0) << std::endl;
  uint32_t entityId = manager.addEntity();
  std::cout << "Created Entity " << entityId << std::endl;
  std::cout << "alive? idx 0 " << manager.isAlive(0) << std::endl;
  PositionManager posManager;
  posManager.registerEntity(entityId, {5.0f, 3.0f});
  std::cout << "nice: " << posManager.getPosition(entityId)
            << "size:" << posManager.dataArray.size() << std::endl;
  SpriteManager spriteManager(posManager, mainCamera);
  Texture monkey("../res/monkey.png");
  spriteManager.registerEntity(entityId, monkey);
  mainCamera.setPositionManager(posManager);
  mainCamera.attachToEntity(entityId);

  Vector2<float> velocity;
  eventPoller.addListener(SDL_KEYDOWN, [&](const SDL_Event& event) {
    if (event.key.repeat) {
      return;
    }
    Vector2<float>& pos = posManager.get(entityId);
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        pos.y += -10;
        velocity.y += -10;
        break;
      case SDLK_RIGHT:
        pos.x += 10;
        velocity.x += 10;
        break;
      case SDLK_DOWN:
        pos.y += 10;
        velocity.y += 10;
        break;
      case SDLK_LEFT:
        pos.x -= 10;
        velocity.x += -10;
        break;
    }
  });

  eventPoller.addListener(SDL_KEYUP, [&](const SDL_Event& event) {
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        velocity.y += 10;
        break;
      case SDLK_RIGHT:
        velocity.x += -10;
        break;
      case SDLK_DOWN:
        velocity.y += -10;
        break;
      case SDLK_LEFT:
        velocity.x += 10;
        break;
    }
  });

  eventPoller.addListener(SDL_MOUSEBUTTONDOWN, [](const SDL_Event& event) {
    Vector2 worldPos =
        mainCamera.toWorldCoords(Vector2(static_cast<float>(event.button.x),
                                         static_cast<float>(event.button.y)));
    printf("screen coords: (%d, %d), world coords: (%.3f, %.3f)\n",
           event.button.x, event.button.y, worldPos.x, worldPos.y);
  });

  eventScheduler.scheduleEvent(
      []() { std::cout << "scheduled event ran" << std::endl; }, 3.0);

  /* Main Game Loop */
  running = true;
  uint32_t lastUpdate = Time::getTicks();
  while (running) {
    uint32_t currentMs = Time::getTicks();
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
    stage.render(mainRenderer, mainCamera);
    renderSystem.renderAll(interpolation);
    spriteManager.renderAll(interpolation);
    mainRenderer.setColor(Colors::WHITE);

    mainRenderer.present();
  }

  return EXIT_SUCCESS;
}