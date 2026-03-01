#include "App.h"

#include "engine/2DGraphics/Rectangle.h"
#include "engine/core/style/BaseColors.h"
#include "Input/InputSystem.h"

using namespace GL;

void App::WorldObjectsInit()
{
    auto rect = std::make_unique<Rectangle>(
        glm::vec3{320.0f, 180.0f, 0.0f},
        glm::vec3{200.0f, 150.0f, 0.0f}
    );

    rect->SetColor(Style::BaseColors::WHITE);
    _objects.emplace_back(std::move(rect));
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

void App::OnInit()
{
    GameTemplate2D::OnInit();
    WorldObjectsInit();
    SetupSystems();
}

void App::OnUpdate(float x)
{
    GameTemplate2D::OnUpdate(x);
}

void App::OnRender()
{
    GameTemplate2D::OnRender();
}

void App::OnShutdown()
{
    GameTemplate2D::OnShutdown();
}
