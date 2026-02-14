#pragma once

#include "GLDependencies.h"
#include "InputKeys.h"
#include "InputState.h"

namespace Systems::Input
{
    inline int ToGLFWKey(Input::Key key)
    {
        switch (key)
        {
        case Key::Escape_Key: return GLFW_KEY_ESCAPE;
        case Key::Enter_Key:  return GLFW_KEY_ENTER;
        case Key::Space_Key:  return GLFW_KEY_SPACE;
        case Key::Num0_Key: return GLFW_KEY_0;
        case Key::Num1_Key: return GLFW_KEY_1;
        case Key::A_Key: return GLFW_KEY_A;
        case Key::B_Key: return GLFW_KEY_B;
        case Key::Z_Key: return GLFW_KEY_Z;
        case Key::Up_Key:    return GLFW_KEY_UP;
        case Key::Down_Key:  return GLFW_KEY_DOWN;
        case Key::Left_Key:  return GLFW_KEY_LEFT;
        case Key::Right_Key: return GLFW_KEY_RIGHT;

        default: return GLFW_KEY_UNKNOWN;
        }
    }

    inline KeyState FromGLFWAction(int action)
    {
        switch (action)
        {
        case GLFW_PRESS:   return KeyState::Press;
        case GLFW_RELEASE: return KeyState::Release;
        case GLFW_REPEAT:  return KeyState::Repeat;
        default:           return KeyState::Release;
        }
    }


}
