#include "App.h"


#include "engine/core/2DGraphics/Rectangle.h"
#include "Input/InputSystem.h"
#include "Objects/Mesh.h"

#include "Shader/Shader.h"
#include "Shader/ShaderManager.h"

using namespace GL;
using namespace Objects;

App::App()
{
    AppInit();
}

App::~App()
{
    Context::Destroy();
}

void App::run()
{
    while (!_window->ShouldClose())
    {
        _window->Clear(
            Color(Style::BaseColors::BLACK)
            );

        Systems::InputSystem::ProcessInput(*_window);

        _shaderProgram.Use();
        Draw();

        _window->SwapBuffers();
        _window->PollEvents();
    }
}

// delete this test function
void App::RunAnimation(float deltaTime)
{
    auto rect1 = _objects.at(0).get();

    if (!moveLeft)
        rect1->Move(_shaderProgram.GetId(), {0.1f * deltaTime, 0.f, 0.f});
    else
        rect1->Move(_shaderProgram.GetId(), {-0.1f * deltaTime, 0.f, 0.f});
}

void App::WorldObjectsInit()
{
    auto rect = std::make_unique<Rectangle>(glm::vec3{-1.0f, 1.0f, 0.0f}, glm::vec3{0.125f, 2.0f, 0.0f});
    rect->SetColor(Style::BaseColors::WHITE);
    _objects.emplace_back(std::move(rect));
}

void App::ContextSetup()
{
    Context::MakeContextCurrent(*_window);
    Context::GladSetup();
    Context::SetUpViewportBasedOnWindow(*_window);
    Context::SetupCallbacks(*_window);
}

void App::AppInit()
{
    Context::Init();

    _window = std::make_unique<Window>( glm::vec2{1280, 720} , "Test App");
    ContextSetup();

    _shaders.emplace_back("../assets/shaders/main_vertex.glsl");
    _shaders.emplace_back("../assets/shaders/main_fragment.glsl");

    _shaderProgram = ShaderManager::CreateShaderProgram(_shaders);

    _shaders.clear();

    WorldObjectsInit();

    SetupSystems();
}

void App::SetupSystems()
{
    Systems::InputSystem::BindAction(
           Systems::Input::Key::A_Key,
           Systems::Input::KeyState::Press,
           [&]()
           {
                moveLeft = true;
           }
       );

    Systems::InputSystem::BindAction(
       Systems::Input::Key::B_Key,
       Systems::Input::KeyState::Press,
       [&]()
       {
            moveLeft = false;
       }
   );
}

void App::Draw()
{
    float lastTime = 0.0f;
   for (auto& object : _objects)
   {
       float currentTime = glfwGetTime();
       float deltaTime = currentTime - lastTime;
       lastTime = currentTime;

       // TODO: use movement / animation system
       RunAnimation(deltaTime); // delete

       object->Draw(_shaderProgram.GetId());
   }
}
