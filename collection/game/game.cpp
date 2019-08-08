#include <gl/glew.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
// #include <gl/GLU.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <thread>

// Note instead of using relative paths, set the include directories
#include "loaders/GlLoader.h"
#include "loaders/SdlLoader.h"

#include "ui/Input.h"
#include "ui/Keyboard.h"
#include "ui/Mouse.h"
#include "ui/Window.h"
#include "ui/WindowBuilder.h"
#include "util/SdlEventPoller.h"

#include "game/Camera.h"

#include "game/GameConstants.h"
#include "game/GameInstance.h"

#include "game/Scene.h"
#include "game/Stage.h"

#include "game/ecs/GameObject.h"
#include "game/ecs/TestComponent.h"
#include "game/ecs/Transform.h"
#include "game/fps/FpsCameraController.h"
#include "graphics/MeshRenderer.h"

#include "game/voxel/BlockDatabase.h"
#include "game/voxel/Chunk.h"
#include "game/voxel/ChunkManager.h"
#include "game/voxel/ChunkMeshBuilder.h"

#include "graphics/Color.h"
#include "graphics/Image.h"
#include "graphics/RenderUnit.h"
#include "graphics/Renderer.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Skybox.h"
#include "graphics/Sprite.h"
#include "graphics/Texture.h"
#include "graphics/Texture2d.h"
#include "graphics/TextureAtlas.h"
#include "graphics/TileMap.h"
#include "graphics/TileSet.h"
#include "graphics/gl/GlClient.h"
#include "graphics/models/CubeMesh.h"
#include "graphics/models/Mesh.h"
#include "graphics/models/PlaneMesh.h"
#include "graphics/models/QuadMesh.h"
#include "graphics/models/SphereMesh.h"

#include "util/Dir2d.h"
#include "util/EventScheduler.h"
#include "util/time/Time.h"

#include "io/File.h"

#include "sys/System.h"

#include "math/Mat4.h"
#include "math/Mathf.h"
#include "math/Vector3.h"
#include "math/geometry/Rect.h"

#include "physics/QuadCollider.h"
#include "physics/RigidBody.h"
#include "physics/SphereCollider.h"

#include "database/RelationalDatabase.h"
#include "io/FileInputStream.h"

#include "references/gl_examples.h"

#include "test/test_collection.h"
#include "util/Macros.h"

#include "datastructures/ObjectPool.h"

int main(int argc, char** argv) {
  test::runBasicTests();
  const std::type_info& info = typeid(RigidBody);
  std::cout << info.name() << std::endl;

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
  windowBuilder.setTitle("Game").setDims(1280, 720).setVisible();
  Window::initMainWindow(windowBuilder);

  Keyboard::init();

  {
    GlLoader loader;
    std::string res = loader.load();
    if (!res.empty()) {
      std::cout << "Could not load OpenGL because of: " << res << std::endl;
    }
  }

  Scene scene;
  Scene::mainScene(scene);

  GameObject& sceneCamera = scene.addGameObject();
  Camera& mainCamera = sceneCamera.addComponent<Camera>();
  sceneCamera.addComponent<TestComponent>();
  sceneCamera.addComponent<FpsCameraController>();
  RigidBody& rbd = sceneCamera.addComponent<RigidBody>();
  rbd.gravityScale = 3;

  RigidBody rbd2 = rbd.copy();
  std::cout << &rbd2.gameObject() << std::endl;
  std::cout << rbd.gravityScale << std::endl;

  ObjectPool<GameObject> objectPool;

  GameObject& sphere = scene.addGameObject();
  sphere.transform().translate(-5, 5, 9);
  sphere.transform().scale(2, 3, 1);
  MeshRenderer& sphereRenderer = sphere.addComponent<MeshRenderer>();
  sphere.addComponent<SphereCollider>();
  sphereRenderer.mesh(SphereMesh());

  GameObject& quad = scene.addGameObject();
  MeshRenderer& quadRenderer = quad.addComponent<MeshRenderer>();
  quad.addComponent<QuadCollider>();
  quadRenderer.mesh(QuadMesh());
  quad.transform().scale(10, 1, 10);
  quad.transform().translate(-5, -5, 9);

  Camera::setMainCamera(mainCamera);
  mainCamera.projectionType = Camera::ProjectionType::PERSPECTIVE;

  GlClient& glClient = GlClient::instance();

  std::optional<ShaderProgram> prog = ShaderProgram::createProgram();
  prog->loadVertFromFile("../res/shaders/lighting.vert");
  prog->loadFragFromFile("../res/shaders/lighting.frag");

  prog->useProgram();
  prog->uniform("u_texture", 0);

  GameObject groundPlane;
  Transform& groundPlaneTransform = groundPlane.transform();
  MeshRenderer& groundRenderer = groundPlane.addComponent<MeshRenderer>();
  groundRenderer.mesh(QuadMesh());

  groundPlaneTransform.scale(100, 1, 100);
  groundPlaneTransform.translate(0, -20, 0);

  unsigned int texture;

  glGenTextures(1, &texture);
  // 0 is active by default so we technically don't need this
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  std::cout << "Loading Voxel Texture Atlas" << std::endl;
  int32_t pixelType = GL_RGB;

  TextureAtlas atlas("../res/toon_voxel.png", 41, 41);
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

  std::array<std::string, 6> skyboxFaces = {"right",  "left",  "top",
                                            "bottom", "front", "back"};

  std::transform(skyboxFaces.begin(), skyboxFaces.end(), skyboxFaces.begin(),
                 [](auto& f) { return "../res/toon_skybox/" + f + ".png"; });

  Skybox skybox(skyboxFaces, "../res/shaders/skybox.vert",
                "../res/shaders/skybox.frag");

  std::cout << "Building Meshes" << std::endl;

  ChunkManager chunkManager = ChunkManager(ChunkMeshBuilder(atlas));

  chunkManager.refreshLoadedChunks(0, 0, 0);
  chunkManager.buildRenders();

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

  TTF_Font* font = TTF_OpenFont("../res/ROCK.ttf", 28);
  SDL_Color color = {34, 34, 34, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(font, "FOO BAR", color);
  SDL_Texture* tex =
      SDL_CreateTextureFromSurface(mainRenderer.getSdlRenderer(), surface);
  SDL_RenderCopy(mainRenderer.getSdlRenderer(), tex, nullptr, nullptr);
  mainRenderer.present();

  System::delay(100);
  TTF_CloseFont(font);

  EventScheduler::scheduleEvent(
      []() { std::cout << "scheduled event ran" << std::endl; }, 3.0);

  /* Main Game Loop */
  double lastRenderTime = Time::programTime();
  double lastUpdate = Time::programTime();
  Time::Internal::init(lastUpdate);

  GameInstance::isRunning = true;
  while (GameInstance::isRunning) {
    double mainLoopStart = Time::programTime();
    double timeSpentUpdating = 0;
    uint32_t numLoops = 0;

    Mat4 PV;
    while ((mainLoopStart - lastUpdate) > GameConstants::frameTime() &&
           numLoops < GameConstants::MAX_LOOPS) {
      Time::Internal::startLoop(lastUpdate);
      EventScheduler::runUpTo(lastUpdate);

      // game code
      int32_t speed = 10;

      float speedScale = 5.0;
      if (Keyboard::keyDown(SDL_SCANCODE_UP)) {
        Camera::getMainCamera().transform().translate(
            mainCamera.transform().front() * Time::deltaTime() * speedScale);
      }
      if (Keyboard::keyDown(SDL_SCANCODE_RIGHT)) {
        Camera::getMainCamera().transform().translate(
            mainCamera.transform().right() * Time::deltaTime() * speedScale);
      }
      if (Keyboard::keyDown(SDL_SCANCODE_LEFT)) {
        Camera::getMainCamera().transform().translate(
            mainCamera.transform().left() * Time::deltaTime() * speedScale);
      }
      if (Keyboard::keyDown(SDL_SCANCODE_DOWN)) {
        Camera::getMainCamera().transform().translate(
            mainCamera.transform().back() * Time::deltaTime() * speedScale);
      }
      if (Keyboard::keyDown(SDL_SCANCODE_W)) {
        Camera::getMainCamera().transform().rotate(
            -Time::deltaTime(), mainCamera.transform().right());
      }
      if (Keyboard::keyDown(SDL_SCANCODE_S)) {
        Camera::getMainCamera().transform().rotate(
            Time::deltaTime(), mainCamera.transform().right());
      }
      if (Keyboard::keyDown(SDL_SCANCODE_A)) {
        Camera::getMainCamera().transform().rotate(-Time::deltaTime(),
                                                   Vec3::up());
      }
      if (Keyboard::keyDown(SDL_SCANCODE_D)) {
        Camera::getMainCamera().transform().rotate(Time::deltaTime(),
                                                   Vec3::up());
      }

      chunkManager.moveCenter(mainCamera.transform().worldPosition());
      sceneCamera.getComponent<RigidBody>().update(Time::deltaTime());
      sceneCamera.getComponent<FpsCameraController>().update(Time::deltaTime());

      Mouse::update();

      Mat4 viewMatrix = Camera::getMainCamera().getViewMatrix();
      Mat4 pMatrix = Camera::getMainCamera().getProjectionMatrix();
      PV = pMatrix * viewMatrix;
      prog->uniform("PV", PV);
      // game code end

      lastUpdate += GameConstants::frameTime();
      timeSpentUpdating += GameConstants::frameTime();
      numLoops++;
    }
    SdlEventPoller::pollEvents();

    float interpolation =
        fmin(1.f, static_cast<float>(mainLoopStart - lastUpdate) /
                      GameConstants::frameTime());

    prog->uniform("u_time", (float)Time::getTicks());

    glClient.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClient.clearAllBuffers();

    skybox.render();

    prog->useProgram();
    glBindTexture(GL_TEXTURE_2D, texture);

    chunkManager.renderChunks();
    std::vector<MeshRenderer*> meshRenderers = MeshRenderer::all();
    for (auto r : meshRenderers) {
      r->render();
    }

    Window::getMainWindow().swapBufferWindow();

    lastRenderTime = Time::programTime();
  }

  return EXIT_SUCCESS;
}
