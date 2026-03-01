#pragma once

#include "GLDependencies.h"

#include <memory>

#include "../style/BaseColors.h"

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
        using Color = Style::BaseColors::Color;

        explicit Window(glm::uvec2 size, const std::string& title);

        [[nodiscard]] GLFWwindow* Get() const
        {
            return _window.get();
        }

        [[nodiscard]] glm::uvec2 GetSize() const
        {
            return _size;
        }

        [[nodiscard]] glm::vec2 GetFramebufferSize() const
        {
            int w, h;
            glfwGetFramebufferSize(_window.get(), &w, &h);
            return glm::vec2(w, h);
        }

        void Viewport();

        [[nodiscard]] bool ShouldClose() const;
        void PollEvents();
        void SwapBuffers();
        void Clear(const Color& color);
    private:
        std::unique_ptr<GLFWwindow, GLFWwindowDeleter> _window;
        glm::uvec2 _size{};
    };
}
