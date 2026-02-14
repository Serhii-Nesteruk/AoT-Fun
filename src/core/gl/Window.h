#pragma once

#include "GLDependencies.h"

#include <memory>

namespace GL
{
    struct GLFWwindowDeleter
    {
        void operator()(GLFWwindow* w) const
        {
            if (w)
            {
                glfwDestroyWindow(w);
            }
        }
    };

    class Window
    {
    public:
        explicit Window(glm::uvec2 size, const std::string& title);

        [[nodiscard]] GLFWwindow* Get() const
        {
            return _window.get();
        }

        [[nodiscard]] glm::uvec2 GetSize() const
        {
            return _size;
        }

        [[nodiscard]] bool ShouldClose() const;
        void PollEvents();
        void SwapBuffers();
        void Clear();
    private:
        std::unique_ptr<GLFWwindow, GLFWwindowDeleter> _window;
        glm::uvec2 _size{};
    };
}
