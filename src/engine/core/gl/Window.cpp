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

void GL::Window::Viewport()
{
    glm::vec2 fbuffSize = GetFramebufferSize();
    glViewport(0, 0, static_cast<int>(fbuffSize.x), static_cast<int>(fbuffSize.y));
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

void GL::Window::Clear(const Color& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

