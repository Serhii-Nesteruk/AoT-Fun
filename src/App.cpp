#include "App.h"

#include <glm/ext/matrix_clip_space.hpp>

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
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    while (!_window->ShouldClose())
    {
        _window->Clear(Style::BaseColors::BLACK);

        Systems::InputSystem::ProcessInput(*_window);

        _shaderProgram->Use();
        Draw();

        _window->SwapBuffers();
        _window->PollEvents();
    }
}

void App::WorldObjectsInit()
{
    auto rect = std::make_unique<Rectangle>(
        glm::vec3{320.0f, 180.0f, 0.0f},
        glm::vec3{200.0f, 150.0f, 0.0f}
        );
    rect->SetColor(Style::BaseColors::WHITE);
    _objects.emplace_back(std::move(rect));
}

void App::ContextSetup()
{
    Context::MakeContextCurrent(*_window);
    Context::GladSetup();
    Context::SetUpViewportBasedOnWindow(*_window);
    Context::SetupCallbacks(*_window);

    CreateRenderContext();
}

void App::AppInit()
{
    Context::Init();

    CreateWindow();
    ContextSetup();
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
    static float lastTime = static_cast<float>(glfwGetTime());
    float currentTime = static_cast<float>(glfwGetTime());
    float dt = currentTime - lastTime;
    lastTime = currentTime;

    FrameContext frame;
    frame.dt = dt;

    float windowWidth = _window->GetFramebufferSize().x;
    float windowHeight = _window->GetFramebufferSize().y;

    glViewport(0, 0, static_cast<int>(windowWidth), static_cast<int>(windowHeight));

    frame.viewProj = glm::ortho(
        0.0f, windowWidth,
        windowHeight, 0.0f,
        -1.0f, 1.0f
    );

    _renderer.BeginFrame(frame);

    for (auto& object : _objects)
    {
        RenderContext ctx{_renderer, *_shaderProgram};
        object->Draw(ctx);
    }

    _renderer.EndFrame();
}

void App::CreateRenderContext()
{
    ShaderVec shaders{};
    shaders.emplace_back("../assets/shaders/main_vertex.glsl");
    shaders.emplace_back("../assets/shaders/main_fragment.glsl");

    _shaderProgram = std::make_unique<ShaderProgram>(ShaderManager::CreateShaderProgram(shaders));
}

void App::CreateWindow()
{
    _window = std::make_unique<Window>( glm::vec2{1280, 720} , "Test App");
}
