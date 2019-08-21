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

#include "network/Server.h"

int main(int argc, char** argv) {
  test::runBasicTests();
  const std::type_info& info = typeid(RigidBody);
  std::cout << info.name() << std::endl;

#ifdef DEBUG
  std::cout << "Starting game..." << std::endl;
#endif
  {
    auto res = SdlLoader::load();
    if (!res.first) {
      std::cout << "Failed to load SDL because of: " << res.second << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  WindowBuilder windowBuilder;
  windowBuilder.setTitle("Game").setDims(1280, 720).setVisible();
  Window::initMainWindow(windowBuilder);

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
  rbd.gravityScale = 0;

  RigidBody rbd2 = rbd.copy();

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

  GlClient& glClient = GlClient::instance();

  std::optional<ShaderProgram> prog = ShaderProgram::createProgram();
  prog->loadVertFromFile("../res/shaders/lighting.vert");
  prog->loadFragFromFile("../res/shaders/lighting.frag");
  prog->useProgram();
  /* Loads sampler2D with Texture0 */
  prog->uniform("u_texture", 0);

  std::optional<ShaderProgram> flat_shader = ShaderProgram::createProgram();
  flat_shader->loadVertFromFile("../res/shaders/opaque_sprite.vert");
  flat_shader->loadFragFromFile("../res/shaders/opaque_sprite.frag");

  GameObject groundPlane;
  Transform& groundPlaneTransform = groundPlane.transform();
  MeshRenderer& groundRenderer = groundPlane.addComponent<MeshRenderer>();
  groundRenderer.mesh(QuadMesh());

  groundPlaneTransform.scale(100, 1, 100);
  groundPlaneTransform.translate(0, -20, 0);

  TextureAtlas atlas("../res/toon_voxel.png", 41, 41);
  Texture2d atlasTexture{atlas};

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

  {
    float vertices[] = {
        0.5f,  0.5f,  0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f   // top left
    };
    float uvs[] = {1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO, UVS;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &UVS);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, UVS);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    flat_shader->useProgram();
    flat_shader->uniform("u_texture", 0);
    atlasTexture.bind();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES,
                   std::distance(std::begin(indices), std::end(indices)),
                   GL_UNSIGNED_INT, 0);

    Window::getMainWindow().swapBufferWindow();
    System::delay(std::chrono::seconds(2));
  }
  GameObject& cube_object = scene.addGameObject();
  MeshRenderer& cube_renderer = cube_object.addComponent<MeshRenderer>();
  cube_renderer.mesh(CubeMesh{});
  cube_object.transform().translate(0, 0, 2);
  cube_object.transform().scale(2);
  mainCamera.projectionType = Camera::ProjectionType::ORTHOGRAPHIC;

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

  Server server{};
  server.launchServer();
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
      if (Keyboard::keyDown(Keyboard::ScanCode::M)) {
        Camera::getMainCamera().projectionType =
            Camera::getMainCamera().projectionType ==
                    Camera::ProjectionType::ORTHOGRAPHIC
                ? Camera::ProjectionType::PERSPECTIVE
                : Camera::ProjectionType::ORTHOGRAPHIC;
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
    atlasTexture.bind();

    chunkManager.renderChunks();
    std::vector<MeshRenderer*> meshRenderers = MeshRenderer::all();
    for (auto r : meshRenderers) {
      r->render();
    }

    Window::getMainWindow().swapBufferWindow();

    lastRenderTime = Time::programTime();
  }

  server.finish();
  return EXIT_SUCCESS;
}
