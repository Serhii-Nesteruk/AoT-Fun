#include "GameTemplate2D.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "Input/InputSystem.h"
#include "Shader/ShaderManager.h"
#include "Context.h"

using namespace GL;
using namespace Objects;

void GameTemplate2D::Run()
{
    AppInit();
    run();
    Shutdown();
}

void GameTemplate2D::run()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    float lastTime = static_cast<float>(glfwGetTime());

    while (!_window->ShouldClose())
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        _window->Clear(Style::BaseColors::BLACK);

        Systems::InputSystem::ProcessInput(*_window);

        OnUpdate(dt);

        _shaderProgram->Use();

        Draw();

        OnRender();

        _window->SwapBuffers();
        _window->PollEvents();
    }
}

void GameTemplate2D::ContextSetup()
{
    Context::MakeContextCurrent(*_window);
    Context::GladSetup();
    Context::SetUpViewportBasedOnWindow(*_window);
    Context::SetupCallbacks(*_window);

    CreateRenderContext();
}

void GameTemplate2D::AppInit()
{
    Context::Init();

    CreateWindow();
    ContextSetup();

    OnInit();
}

void GameTemplate2D::Draw()
{
    static float lastTime = static_cast<float>(glfwGetTime());
    float currentTime = static_cast<float>(glfwGetTime());
    float dt = currentTime - lastTime;
    lastTime = currentTime;

    FrameContext frame;
    frame.dt = dt;

    glm::vec2 frameBuffSize = _window->GetFramebufferSize();

    _window->Viewport();

    frame.viewProj = glm::ortho(
        0.0f, frameBuffSize.x,
        frameBuffSize.y, 0.0f,
        -1.0f, 1.0f
    );

    _renderer.BeginFrame(frame);

    for (auto& object : _objects)
    {
        RenderContext ctx{ _renderer, *_shaderProgram };
        object->Draw(ctx);
    }

    _renderer.EndFrame();
}

void GameTemplate2D::CreateRenderContext()
{
    ShaderVec shaders = GetDefaultShaders();

    _shaderProgram = std::make_unique<GL::ShaderProgram>(
        ShaderManager::CreateShaderProgram(shaders)
    );
}

void GameTemplate2D::CreateWindow()
{
    const auto [size, title] = GetDefaultWindowParams();
    _window = std::make_unique<GL::Window>(size, title);
}

void GameTemplate2D::Shutdown()
{
    OnShutdown();
    Context::Destroy();
}

std::pair<glm::vec2, const char*> GameTemplate2D::GetDefaultWindowParams() const
{
    return { glm::vec2{1280, 720}, "Test App" };
}

GameTemplate2D::ShaderVec GameTemplate2D::GetDefaultShaders() const
{
    ShaderVec shaders{};
    shaders.emplace_back("../assets/shaders/main_vertex.glsl");
    shaders.emplace_back("../assets/shaders/main_fragment.glsl");
    return shaders;
}