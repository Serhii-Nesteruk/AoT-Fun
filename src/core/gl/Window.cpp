#include "Window.h"

#include "Context.h"

GL::Window::Window(glm::uvec2 size, const std::string& title)
    : _size(size)
{
    if (!Context::IsGLFWInitialized())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    _window.reset(glfwCreateWindow(
            _size.x, _size.y, title.c_str(), nullptr, nullptr
            ));

   if (!_window)
   {
       throw std::runtime_error("Failed to create GLFW window");
   }
}

bool GL::Window::ShouldClose() const
{
    return glfwWindowShouldClose(_window.get());
}

void GL::Window::PollEvents()
{
    Context::PollEvents();
}

void GL::Window::SwapBuffers()
{
    Context::SwapBuffers(*this);
}

void GL::Window::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

