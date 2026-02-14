#include "Context.h"

#include <stdexcept>

bool GL::Context::_isGLFWInitialized = false;
bool GL::Context::Config::shouldDecorateWindow = GLFW_TRUE;

void GL::Context::Init()
{
    GlfwSetup();
}

void GL::Context::Destroy()
{
    if (_isGLFWInitialized)
        glfwTerminate();
}

void GL::Context::MakeContextCurrent(const Window& window)
{
    glfwMakeContextCurrent(window.Get());
}

bool GL::Context::IsGLFWInitialized()
{
    return _isGLFWInitialized;
}

void GL::Context::SetUpViewportBasedOnWindow(const Window& window)
{
    SetViewport(0, 0, window.GetSize().x, window.GetSize().y);
}

void GL::Context::SetViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void GL::Context::SetupCallbacks(const Window& window)
{
    glfwSetFramebufferSizeCallback(window.Get(), FramebufferSizeCallback);
}

void GL::Context::SwapBuffers(const Window& window)
{
    glfwSwapBuffers(window.Get());
}

void GL::Context::PollEvents()
{
    glfwPollEvents();
}

void GL::Context::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    SetViewport(0, 0, width, height);
}

void GL::Context::GlfwSetup()
{
    if (!glfwInit())
    {
        throw std::runtime_error("GL::Context: Failed to initialize GLFW");
    }
    _isGLFWInitialized = true;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Config::MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Config::MINOR);
    glfwWindowHint(GLFW_DECORATED, Config::shouldDecorateWindow);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GL::Context::GladSetup()
{
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}
