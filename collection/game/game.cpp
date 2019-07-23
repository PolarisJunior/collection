
#include <gl/glew.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
// #include <gl/GLU.h>

#include <algorithm>
#include <iostream>
#include <memory>

// Note instead of using relative paths, set the include directories
#include "loaders/GlLoader.h"
#include "loaders/SdlLoader.h"

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

#include "game/ecs/Transform.h"

#include "graphics/Color.h"
#include "graphics/Image.h"
#include "graphics/Renderer.h"
#include "graphics/Sprite.h"
#include "graphics/Texture.h"
#include "graphics/TileMap.h"
#include "graphics/TileSet.h"
#include "graphics/models/CubeMesh.h"
#include "graphics/models/Mesh.h"
#include "graphics/models/SphereMesh.h"

#include "graphics/ShaderProgram.h"
#include "graphics/gl/GlClient.h"

#include "math/geometry/Rect.h"
#include "util/Dir2d.h"
#include "util/EventScheduler.h"

#include "io/File.h"

#include "network/ClientSocket.h"
#include "network/ServerSocket.h"
#include "network/Socket.h"

#include "sys/System.h"

#include "math/Mat4.h"
#include "math/Mathf.h"
#include "math/Vector3.h"

#include "database/RelationalDatabase.h"
#include "io/FileInputStream.h"

#include "references/gl_examples.h"

static bool running;
static SdlEventPoller eventPoller;

static const uint32_t UPDATE_FREQUENCY = 60;
static const uint32_t UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;
static const uint32_t MAX_LOOPS = 10;

static Actor actor;

EventScheduler eventScheduler;

void render();

int main(int argc, char** argv) {
  {
    SdlLoader sdlLoader;
    auto res = sdlLoader.load();
    if (!res.first) {
      std::cout << "Failed to load SDL because of: " << res.second << std::endl;
      exit(EXIT_FAILURE);
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
  Window::initMainWindow(windowBuilder);

  {
    GlLoader loader;
    std::string res = loader.load();
    if (!res.empty()) {
      std::cout << "Could not load OpenGL because of: " << res << std::endl;
    }
  }

  Camera mainCamera;
  mainCamera.fieldOfView = 100;
  Camera::setMainCamera(mainCamera);
  mainCamera.projectionType = Camera::ProjectionType::PERSPECTIVE;

  GlClient glClient;

  std::cout << CubeMesh::cubeNormals.size() << " "
            << CubeMesh::cubeVertices.size() << std::endl;

  Transform transform;
  transform.translate(Vec3(-10, -5, -.3));
  transform.rotate(Mathf::pi_4, 0, 1, 0);
  transform.scale(2, 2, 2);

  Mat4 model = transform.getModelMatrix();

  Camera::getMainCamera().transform.translate(Vec3(0, 0, 0));
  std::cout << "before" << mainCamera.transform.front() << "\n";
  // Camera::getMainCamera().transform.rotate(Mathf::pi, Vec3(0, 0, 0));
  std::cout << "after" << mainCamera.transform.front() << "\n";

  Mat4 pMatrix = Camera::getMainCamera().getProjectionMatrix();
  Mat4 vMatrix = Camera::getMainCamera().getViewMatrix();

  std::optional<ShaderProgram> prog = ShaderProgram::createProgram();
  prog->loadVertFromFile("../res/simple.vert");
  prog->loadFragFromFile("../res/simple.frag");

  prog->linkProgram();

  CubeMesh cubeMesh;
  SphereMesh sphereMesh;

  // unsigned int VBO, VAO, EBO;
  uint32_t vao = glClient.sendMesh(cubeMesh);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default
                               // wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  SDL_Surface* surf = IMG_Load("../res/monkey.png");
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, surf->pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
  SDL_FreeSurface(surf);

  prog->useProgram();

  // glUniform1i(glGetUniformLocation(prog->getProgramHandle(), "u_texture"),
  // 0);

  glBindVertexArray(
      vao);  // seeing as we only have a single VAO there's no need to bind it
             // every time, but we'll do so to keep things a bit more organized
  // Mat4 modelNormal = transform.localRotation().toMatrix()
  prog->uniform("model", model);
  prog->uniform("view", vMatrix);
  prog->uniform("projection", pMatrix);

  prog->uniform("u_texture", 0);

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

  System::delay(100);
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
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.front());
      }
      if (keyboard.keyDown(SDL_SCANCODE_RIGHT)) {
        velocity += Dir2d::dirVectors[Dir2d::RIGHT];
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.right());
      }
      if (keyboard.keyDown(SDL_SCANCODE_LEFT)) {
        velocity += Dir2d::dirVectors[Dir2d::LEFT];
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.left());
      }
      if (keyboard.keyDown(SDL_SCANCODE_DOWN)) {
        velocity += Dir2d::dirVectors[Dir2d::DOWN];
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.back());
      }
      if (keyboard.keyDown(SDL_SCANCODE_W)) {
        Camera::getMainCamera().transform.translate(mainCamera.transform.up());
      }
      if (keyboard.keyDown(SDL_SCANCODE_S)) {
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.down());
      }
      if (keyboard.keyDown(SDL_SCANCODE_A)) {
        Camera::getMainCamera().transform.rotate(-.05, Vec3::up());
      }
      if (keyboard.keyDown(SDL_SCANCODE_D)) {
        Camera::getMainCamera().transform.rotate(.05, Vec3::up());
      }
      if (keyboard.keyDown(SDL_SCANCODE_Z)) {
        transform.rotate(.01, 0, 1, 0);
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

    // mainRenderer.setColor(Colors::BLACK);
    // mainRenderer.clear();
    // stage.render(mainRenderer, mainCamera);
    // renderSystem.renderAll(interpolation);
    // spriteManager.renderAll(interpolation);
    // mainRenderer.setColor(Colors::WHITE);
    // mainRenderer.present();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vMatrix = Camera::getMainCamera().getViewMatrix();
    model = transform.getModelMatrix();
    prog->uniform("view", vMatrix);
    prog->uniform("model", model);
    prog->uniform("model_normal", transform.localRotation().toMatrix());
    prog->uniform("u_time", (float)Time::getTicks());
    glDrawElements(GL_TRIANGLES, SphereMesh::sphereTriangles.size(),
                   GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLES, 0, 6);
    Window::getMainWindow().swapBufferWindow();
    render();

    // For calculating FPS
    renderCount++;
    if (renderCount % 100 == 0) {
      std::cout << mainCamera.transform.localPosition() << std::endl;
      std::cout << "forward" << mainCamera.transform.front() << "up "
                << mainCamera.transform.up() << " right"
                << mainCamera.transform.right() << std::endl;

      uint32_t msSinceLastFpsCalc =
          std::max<int>(Time::getTicks() - lastRender, 1);
      // std::cout << 100 * 1000 / msSinceLastFpsCalc << "fps" << std::endl;
      uint32_t curFps = 100 * 1000 / msSinceLastFpsCalc;
      fpsText = std::to_string(curFps);
      lastRender += msSinceLastFpsCalc;

      // 100 / msSinceLastFpsCalc = renders per ms
      // 1000*100/ msSinceLastFpsCount = renders per second
    }
  }

  return EXIT_SUCCESS;
}

void render() {}