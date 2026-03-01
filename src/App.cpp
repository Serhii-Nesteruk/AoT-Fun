#include "App.h"

#include "CircleShape.h"
#include "EllipseShape.h"
#include "LineShape.h"
#include "PolygonShape.h"
#include "RectangleShape.h"
#include "RingShape.h"
#include "engine/shapes/Shape2D.h"
#include "engine/core/style/BaseColors.h"
#include "Input/InputSystem.h"

using namespace GL;

void App::WorldObjectsInit()
{
    auto rect = std::make_unique<RectangleShape>(
        glm::vec3{800, 400, 0},
        glm::vec3{200, 150, 0},
        Style::BaseColors::WHITE
    );
    _objects.emplace_back(std::move(rect));

    _texture = std::make_unique<Texture2D>("../assets/textures/test.png");
    auto spr = std::make_unique<RectangleShape>(
        glm::vec3{1000, 400, 0},
        glm::vec3{256, 256, 0},
        Style::BaseColors::WHITE
    );
    static_cast<Shape2D*>(spr.get())->SetTexture(_texture.get());
    _objects.emplace_back(std::move(spr));

    _objects.emplace_back(std::make_unique<CircleShape>(
        glm::vec3{100, 100, 0}, 60.0f, 48, Style::BaseColors::WHITE
    ));

    _objects.emplace_back(std::make_unique<EllipseShape>(
        glm::vec3{300, 120, 0}, 80.0f, 40.0f, 64, Style::BaseColors::WHITE
    ));

    _objects.emplace_back(std::make_unique<PolygonShape>(
        glm::vec3{500, 100, 0}, 70.0f, 6, Style::BaseColors::WHITE
    ));

    _objects.emplace_back(std::make_unique<RingShape>(
        glm::vec3{700, 80, 0}, 40.0f, 60.0f, 96, Style::BaseColors::WHITE
    ));

    _objects.emplace_back(std::make_unique<LineShape>(
        glm::vec3{100, 300, 0}, glm::vec2{0,0}, glm::vec2{300,120}, Style::BaseColors::WHITE
    ));
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
