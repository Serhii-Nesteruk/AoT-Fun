#pragma once

#include "GLDependencies.h"
#include "Window.h"

namespace GL
{
    class Context
    {
    public:
        struct Config
        {
            static constexpr int MAJOR = 3;
            static constexpr int MINOR = 3;
            static glm::dvec2 windowSize;
            static bool shouldDecorateWindow;
        };

        static void Init();
        static void Destroy();

        static void MakeContextCurrent(const Window& window);

        static bool IsGLFWInitialized();

        static void SetUpViewportBasedOnWindow(const Window& window);
        static void SetViewport(int x, int y, int width, int height);
        static void SetupCallbacks(const Window& window);

        static void SwapBuffers(const Window& window);
        static void PollEvents();

        static void GladSetup();
    private:
        static void GlfwSetup();

        static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

    private:
        static bool _isGLFWInitialized;
    };
}
