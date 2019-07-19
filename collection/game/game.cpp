
#include <gl/glew.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
// #include <gl/GLU.h>

#include <iostream>
#include <memory>

// Note instead of using relative paths, set the include directories
#include "datastructures/Trie.h"
#include "misc/arrayHopper.h"

#include "graphics/GlLoader.h"

#include "ui/Input.h"
#include "ui/Keyboard.h"
#include "ui/Mouse.h"
#include "ui/SdlEventPoller.h"
#include "ui/Window.h"
#include "ui/WindowBuilder.h"
#include "util/time/Time.h"

#include "game/Actor.h"
#include "game/Camera.h"
#include "game/Component.h"
#include "game/GameInstance.h"
#include "game/RenderComponent.h"
#include "game/RenderSystem.h"
#include "game/Stage.h"
#include "game/ecs/EntityManager.h"
#include "game/ecs/PositionManager.h"
#include "game/ecs/SpriteManager.h"

#include "graphics/Color.h"
#include "graphics/Image.h"
#include "graphics/Renderer.h"
#include "graphics/Sprite.h"
#include "graphics/Texture.h"
#include "graphics/TileMap.h"
#include "graphics/TileSet.h"

#include "math/geometry/Rect.h"
#include "util/Dir2d.h"
#include "util/EventScheduler.h"

#include "io/File.h"

#include "network/ClientSocket.h"
#include "network/ServerSocket.h"
#include "network/Socket.h"

#include "sys/System.h"

#include "math/Vector3.h"

#include "database/RelationalDatabase.h"
#include "io/FileInputStream.h"

static bool running;
static SdlEventPoller eventPoller;

static const uint32_t UPDATE_FREQUENCY = 60;
static const uint32_t UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;
static const uint32_t MAX_LOOPS = 10;

static Actor actor;

EventScheduler eventScheduler;

int main(int argc, char** argv) {
  SDL_LogError(SDL_LOG_CATEGORY_ERROR, "how now");
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    printf("%s 1\n", SDL_GetError());
    // SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
    exit(EXIT_FAILURE);
  }
  {
    uint32_t flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if (IMG_Init(flags) != flags) {
      printf("%s 2\n", IMG_GetError());
      // SDL_LogError(SDL_LOG_CATEGORY_ERROR, IMG_GetError());
      exit(EXIT_FAILURE);
    }
  }
  if (TTF_Init() != 0) {
    printf("%s 3\n", TTF_GetError());
    // SDL_LogError(SDL_LOG_CATEGORY_ERROR, TTF_GetError());
    exit(EXIT_FAILURE);
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
  Window::initMainWindow(windowBuilder);

  GlLoader::initialize();

  GLuint gProgramId = glCreateProgram();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* vertexShaderSource[] = {
      "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( "
      "LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"};

  glShaderSource(vertexShader, 1, vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  GLint vShaderCompiled = GL_FALSE;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
  if (vShaderCompiled != GL_TRUE) {
    std::cout << "unable to compile vertex shader: " << vertexShader
              << std::endl;
  }

  glAttachShader(gProgramId, vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* fragmentShaderSource[] = {
      "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, "
      "1.0, 1.0, 1.0 ); }"};

  glShaderSource(fragmentShader, 1, fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  GLint fShaderCompiled = GL_FALSE;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
  if (fShaderCompiled != GL_TRUE) {
    std::cout << "Unable to compile fragment shader" << fragmentShader
              << std::endl;
  }

  glAttachShader(gProgramId, fragmentShader);
  glLinkProgram(gProgramId);
  GLint programSuccess = GL_TRUE;
  glGetProgramiv(gProgramId, GL_LINK_STATUS, &programSuccess);
  if (programSuccess != GL_TRUE) {
    printf("Error linking program %d!\n", gProgramId);
  }
  GLint gVertexPos2DLocation = glGetAttribLocation(gProgramId, "LVertexPos2D");
  if (gVertexPos2DLocation == -1) {
    printf("LVertexPos2D is not a valid glsl program variable!\n");
  }

  // Initialize clear color
  glClearColor(1.f, 0.f, 0.f, 1.f);

  // VBO data
  GLfloat vertexData[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f};

  // IBO data
  GLuint indexData[] = {0, 1, 2, 3};

  GLuint gVBO = 0;
  GLuint gIBO = 0;

  // Create VBO
  glGenBuffers(1, &gVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData,
               GL_STATIC_DRAW);

  // Create IBO
  glGenBuffers(1, &gIBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData,
               GL_STATIC_DRAW);

  glClear(GL_COLOR_BUFFER_BIT);
  // Bind program
  glUseProgram(gProgramId);

  // Enable vertex position
  glEnableVertexAttribArray(gVertexPos2DLocation);

  // Set vertex data
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE,
                        2 * sizeof(GLfloat), NULL);

  // Set index data and render
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

  // Disable vertex position
  glDisableVertexAttribArray(gVertexPos2DLocation);

  // Unbind program
  glUseProgram(NULL);
  SDL_GL_SwapWindow(Window::getMainWindow().getSdlWindow());

  System::delay(500);
  Renderer& mainRenderer = Window::getMainRenderer();

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

  Camera mainCamera;
  Camera::setMainCamera(mainCamera);

  mainCamera.setWidth(static_cast<float>(Window::getMainWindow().getWidth()));
  mainCamera.setHeight(static_cast<float>(Window::getMainWindow().getHeight()));

  actor.x = 0;
  actor.y = 0;
  mainCamera.moveCamera(0, 0);
  mainCamera.attachToActor(&actor);
  mainCamera.setAttachOffset(Vector2(100.0f, 100.0f));

  RenderComponent renderComp;
  Sprite playerSprite("../res/monkey.png");
  actor.attachComponent(renderComp);
  actor.attachComponent(playerSprite);

  EntityManager& manager = GameInstance::instance().entityManager();
  uint32_t entityId = manager.addEntity();

  PositionManager& posManager = GameInstance::instance().posManager();
  posManager.registerEntity(entityId, {5.0f, 3.0f});

  SpriteManager spriteManager(posManager, mainCamera);
  Texture monkey("../res/monkey.png");
  spriteManager.registerEntity(entityId, monkey);
  mainCamera.setPositionManager(posManager);
  mainCamera.attachToEntity(entityId);

  TTF_Font* font = TTF_OpenFont("../res/ROCK.ttf", 28);
  SDL_Color color = {34, 34, 34, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(font, "foo bar", color);
  SDL_Texture* tex =
      SDL_CreateTextureFromSurface(mainRenderer.getSdlRenderer(), surface);
  SDL_RenderCopy(mainRenderer.getSdlRenderer(), tex, nullptr, nullptr);
  mainRenderer.present();
  // mainRenderer.getSdlRenderer();
  System::delay(5000);
  TTF_CloseFont(font);

  Vector2<float>& pos = posManager.get(entityId);
  eventPoller.addListener(SDL_KEYDOWN, [&](const SDL_Event& event) {
    if (event.key.repeat) {
      return;
    }

    switch (event.key.keysym.sym) {
      case SDLK_UP:
        // pos.y += -10;
        // velocity.y += -10;
        break;
      case SDLK_RIGHT:
        // pos.x += 10;
        // velocity.x += 10;
        break;
      case SDLK_DOWN:
        // pos.y += 10;
        // velocity.y += 10;
        break;
      case SDLK_LEFT:
        // pos.x -= 10;
        // velocity.x += -10;
        break;
    }
  });

  eventPoller.addListener(SDL_KEYUP, [&](const SDL_Event& event) {
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        // velocity.y += 10;
        break;
      case SDLK_RIGHT:
        // velocity.x += -10;
        break;
      case SDLK_DOWN:
        // velocity.y += -10;
        break;
      case SDLK_LEFT:
        // velocity.x += 10;
        break;
    }
  });

  eventPoller.addListener(SDL_MOUSEBUTTONDOWN, [](const SDL_Event& event) {
    Vector2 worldPos = Camera::getMainCamera().toWorldCoords(
        Vector2(static_cast<float>(event.button.x),
                static_cast<float>(event.button.y)));
    printf("screen coords: (%d, %d), world coords: (%.3f, %.3f)\n",
           event.button.x, event.button.y, worldPos.x, worldPos.y);
  });

  eventScheduler.scheduleEvent(
      []() { std::cout << "scheduled event ran" << std::endl; }, 3.0);

  std::string fpsText = "";
  uint32_t lastRender = Time::getTicks();
  uint32_t renderCount = 0;
  /* Main Game Loop */
  running = true;
  uint32_t lastUpdate = Time::getTicks();
  while (running) {
    uint32_t currentMs = Time::getTicks();
    uint32_t frameTime = 0;
    uint32_t numLoops = 0;

    while ((currentMs - lastUpdate) > UPDATE_PERIOD && numLoops < MAX_LOOPS) {
      eventScheduler.runUpTo(lastUpdate);

      // game code
      Vector2<float> velocity{0.0f, 0.0f};
      int32_t speed = 10;
      Keyboard& keyboard = GameInstance::instance().keyboard();
      if (keyboard.keyDown(SDL_SCANCODE_UP)) {
        velocity += Dir2d::dirVectors[Dir2d::UP];
      }
      if (keyboard.keyDown(SDL_SCANCODE_RIGHT)) {
        velocity += Dir2d::dirVectors[Dir2d::RIGHT];
      }
      if (keyboard.keyDown(SDL_SCANCODE_LEFT)) {
        velocity += Dir2d::dirVectors[Dir2d::LEFT];
      }
      if (keyboard.keyDown(SDL_SCANCODE_DOWN)) {
        velocity += Dir2d::dirVectors[Dir2d::DOWN];
      }

      velocity.normalize() *= speed;
      pos += velocity;
      // game code end

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

    // For calculating FPS
    renderCount++;
    if (renderCount % 100 == 0) {
      uint32_t msSinceLastFpsCalc = Time::getTicks() - lastRender;
      std::cout << 100 * 1000 / msSinceLastFpsCalc << "fps" << std::endl;
      uint32_t curFps = 100 * 1000 / msSinceLastFpsCalc;
      fpsText = std::to_string(curFps);
      lastRender += msSinceLastFpsCalc;
      // 100 / msSinceLastFpsCalc = renders per ms
      // 1000*100/ msSinceLastFpsCount = renders per second
    }
  }

  return EXIT_SUCCESS;
}