#include "App.h"

#include "engine/2DGraphics/Rectangle.h"
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

void App::WorldObjectsInit()
{
    auto rect = std::make_unique<Rectangle>(glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec3{1.0f, 1.0f, 0.0f});
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
           Systems::Input::Key::Escape_Key,
           Systems::Input::KeyState::Press,
           [&]()
           {
                glfwSetWindowShouldClose(_window->Get(), GL_TRUE);
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

       object->Draw(_shaderProgram.GetId());
   }
}
