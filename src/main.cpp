#include <iostream>

#include "Context.h"

int main()
{
    try
    {
        using namespace GL;
        using Color = Style::BaseColors::Color;

        Context::Init();

        Window window({1280, 720}, "AoT");

        Context::MakeContextCurrent(window);
        Context::GladSetup();
        Context::SetUpViewportBasedOnWindow(window);
        Context::SetupCallbacks(window);

        while (!window.ShouldClose())
        {
            window.Clear(
                Color(
                     Color::FloatToU8(0.2f),
                    Color::FloatToU8(0.3f),
                    Color::FloatToU8(0.3f)
                    ) /* blue-gray */
                );
            window.SwapBuffers();
            window.PollEvents();
        }

        Context::Destroy();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        GL::Context::Destroy();
        return -1;
    }
    return 0;
}
