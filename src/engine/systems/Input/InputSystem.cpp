#include "InputSystem.h"
#include "Context.h"
#include <stdexcept>

#include "InputKeyMapping.h"

std::unordered_map<int, Systems::InputSystem::Action>
    Systems::InputSystem::_actions{};

namespace
{
    int MakeActionId(Systems::Input::Key key, Systems::Input::KeyState state)
    {
        return (static_cast<int>(key) << 8) | static_cast<int>(state);
    }
}

void Systems::InputSystem::BindAction(
    Input::Key key,
    Input::KeyState state,
    Action action)
{
    _actions[MakeActionId(key, state)] = std::move(action);
}

void Systems::InputSystem::ProcessInput(const GL::Window& window)
{
    if (!GL::Context::IsGLFWInitialized())
        throw std::runtime_error("InputSystem: GLFW not initialized");

    for (auto& [id, action] : _actions)
    {
        Input::Key key = static_cast<Input::Key>(id >> 8);
        Input::KeyState state = static_cast<Input::KeyState>(id & 0xFF);

        int glfwKey = Input::ToGLFWKey(key);
        int glfwState = glfwGetKey(window.Get(), glfwKey);

        if ((glfwState == GLFW_PRESS && state == Input::KeyState::Press) ||
            (glfwState == GLFW_REPEAT && state == Input::KeyState::Repeat))
        {
            action();
        }
    }
}
