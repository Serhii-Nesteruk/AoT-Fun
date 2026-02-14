#pragma once


#include "Context.h"
#include "InputState.h"
#include "InputKeys.h"

#include <functional>

namespace Systems
{
    class InputSystem
    {
    public:
        using Action = std::function<void()>;

        static void ProcessInput(const GL::Window& window);

        static void BindAction(Input::Key key, Input::KeyState state, Action action);

    private:
        static std::unordered_map<int, Action> _actions;
    };
}