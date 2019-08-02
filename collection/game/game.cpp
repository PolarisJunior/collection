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

#include "game/voxel/BlockDatabase.h"
#include "game/voxel/Chunk.h"
#include "game/voxel/ChunkManager.h"
#include "game/voxel/ChunkMeshBuilder.h"

#include "graphics/Color.h"
#include "graphics/Image.h"
#include "graphics/RenderActor.h"
#include "graphics/RenderUnit.h"
#include "graphics/Renderer.h"
#include "graphics/Skybox.h"
#include "graphics/Sprite.h"
#include "graphics/Texture.h"
#include "graphics/TextureAtlas.h"
#include "graphics/TileMap.h"
#include "graphics/TileSet.h"
#include "graphics/models/CubeMesh.h"
#include "graphics/models/Mesh.h"
#include "graphics/models/PlaneMesh.h"
#include "graphics/models/QuadMesh.h"
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

#include "test/test_collection.h"
#include "util/Macros.h"

static bool running;
static SdlEventPoller eventPoller;

static const uint32_t UPDATE_FREQUENCY = 60;
static const uint32_t UPDATE_PERIOD = 1000 / UPDATE_FREQUENCY;
static const uint32_t MAX_LOOPS = 10;

static Actor actor;

EventScheduler eventScheduler;

int main(int argc, char** argv) {
  test::runBasicTests();
#ifdef DEBUG
  std::cout << "Starting game..." << std::endl;
#endif
  {
    SdlLoader sdlLoader;
    auto res = sdlLoader.load();
    if (!res.first) {
      std::cout << "Failed to load SDL because of: " << res.second << std::endl;
      exit(EXIT_FAILURE);
    }
  }

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
  Camera::setMainCamera(mainCamera);
  mainCamera.fieldOfView = 90;
  mainCamera.projectionType = Camera::ProjectionType::PERSPECTIVE;

  GlClient& glClient = GlClient::instance();

  std::optional<ShaderProgram> prog = ShaderProgram::createProgram();
  prog->loadVertFromFile("../res/shaders/lighting.vert");
  prog->loadFragFromFile("../res/shaders/lighting.frag");

  prog->useProgram();

  Transform groundPlaneTransform;
  groundPlaneTransform.scale(100, 1, 100);
  groundPlaneTransform.translate(0, -20, 0);

  unsigned int texture;
  glGenTextures(1, &texture);
  // 0 is active by default so we technically don't need this
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  std::cout << "Loading Voxel Texture Atlas" << std::endl;
  int32_t pixelType = GL_RGB;
  // TextureAtlas atlas("../res/minecraft.jpg", 64, 64);
  // TextureAtlas atlas("../res/wac.png", 41, 41);
  TextureAtlas atlas("../res/toon_voxel.png", 41, 41);
  // TextureAtlas atlas("../res/spritesheet_tiles2.png", 32, 32);
  if (atlas.hasAlpha()) {
    pixelType = GL_RGBA;
  }
  glTexImage2D(GL_TEXTURE_2D, 0, pixelType, atlas.width(), atlas.height(), 0,
               pixelType, GL_UNSIGNED_BYTE, atlas.dataPointer());

  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

  prog->uniform("u_texture", 0);

  std::array<std::string, 6> skyboxFaces = {"right",  "left",  "top",
                                            "bottom", "front", "back"};

  std::transform(skyboxFaces.begin(), skyboxFaces.end(), skyboxFaces.begin(),
                 [](auto& f) { return "../res/toon_skybox/" + f + ".png"; });

  Skybox skybox(skyboxFaces, "../res/shaders/skybox.vert",
                "../res/shaders/skybox.frag");

  std::cout << "Building Meshes" << std::endl;
  std::vector<RenderActor> renderActors;

  ChunkManager chunkManager = ChunkManager(ChunkMeshBuilder(atlas));

  chunkManager.refreshLoadedChunks(0, 0, 0);
  chunkManager.buildRenders();

  renderActors.push_back(RenderActor(QuadMesh(), groundPlaneTransform));

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
  SDL_Surface* surface = TTF_RenderText_Solid(font, "FOO BAR", color);
  SDL_Texture* tex =
      SDL_CreateTextureFromSurface(mainRenderer.getSdlRenderer(), surface);
  SDL_RenderCopy(mainRenderer.getSdlRenderer(), tex, nullptr, nullptr);
  mainRenderer.present();

  System::delay(100);
  TTF_CloseFont(font);

  Vector2<float>& pos = posManager.get(entityId);
  eventPoller.addListener(SDL_KEYDOWN, [](const SDL_Event& event) {
    if (event.key.repeat) {
      return;
    }
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        break;
      case SDLK_RIGHT:
        break;
      case SDLK_DOWN:
        break;
      case SDLK_LEFT:
        break;
    }
  });

  eventPoller.addListener(SDL_KEYUP, [](const SDL_Event& event) {
    switch (event.key.keysym.sym) {
      case SDLK_UP:
        break;
      case SDLK_RIGHT:
        break;
      case SDLK_DOWN:
        break;
      case SDLK_LEFT:
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

    Mat4 PV;
    while ((currentMs - lastUpdate) > UPDATE_PERIOD && numLoops < MAX_LOOPS) {
      Time::Internal::startLoop(lastUpdate);
      eventScheduler.runUpTo(lastUpdate);

      // game code
      Vector2<float> velocity{0.0f, 0.0f};
      int32_t speed = 10;
      Keyboard& keyboard = GameInstance::instance().keyboard();

      float speedScale = 5.0;
      if (keyboard.keyDown(SDL_SCANCODE_UP)) {
        velocity += Dir2d::dirVectors[Dir2d::UP];
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.front() * Time::deltaTime() * speedScale);
      }
      if (keyboard.keyDown(SDL_SCANCODE_RIGHT)) {
        velocity += Dir2d::dirVectors[Dir2d::RIGHT];
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.right() * Time::deltaTime() * speedScale);
      }
      if (keyboard.keyDown(SDL_SCANCODE_LEFT)) {
        velocity += Dir2d::dirVectors[Dir2d::LEFT];
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.left() * Time::deltaTime() * speedScale);
      }
      if (keyboard.keyDown(SDL_SCANCODE_DOWN)) {
        velocity += Dir2d::dirVectors[Dir2d::DOWN];
        Camera::getMainCamera().transform.translate(
            mainCamera.transform.back() * Time::deltaTime() * speedScale);
      }
      if (keyboard.keyDown(SDL_SCANCODE_W)) {
        Camera::getMainCamera().transform.rotate(-Time::deltaTime(),
                                                 mainCamera.transform.right());
      }
      if (keyboard.keyDown(SDL_SCANCODE_S)) {
        Camera::getMainCamera().transform.rotate(Time::deltaTime(),
                                                 mainCamera.transform.right());
      }
      if (keyboard.keyDown(SDL_SCANCODE_A)) {
        Camera::getMainCamera().transform.rotate(-Time::deltaTime(),
                                                 Vec3::up());
      }
      if (keyboard.keyDown(SDL_SCANCODE_D)) {
        Camera::getMainCamera().transform.rotate(Time::deltaTime(), Vec3::up());
      }

      // chunkManager.moveCenter(mainCamera.transform.worldPosition());

      velocity.normalize() *= speed;
      pos += velocity;

      Mat4 viewMatrix = Camera::getMainCamera().getViewMatrix();
      Mat4 pMatrix = Camera::getMainCamera().getProjectionMatrix();
      PV = pMatrix * viewMatrix;
      prog->uniform("PV", PV);
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
    prog->uniform("u_time", (float)Time::getTicks());

    glClient.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClient.clearAllBuffers();

    skybox.render();

    prog->useProgram();
    glBindTexture(GL_TEXTURE_2D, texture);

    chunkManager.renderChunks();
    // for (RenderActor& renderActor : renderActors) {
    //   renderActor.render();
    // }

    Window::getMainWindow().swapBufferWindow();

    // For calculating FPS
    renderCount++;
    if (renderCount % 100 == 0) {
      uint32_t msSinceLastFpsCalc =
          std::max<int>(Time::getTicks() - lastRender, 1);

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
