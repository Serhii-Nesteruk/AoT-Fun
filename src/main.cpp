#include <filesystem>
#include <iostream>

#include "Context.h"
#include "App.h"
#include "Input/InputSystem.h"
#include "Objects/Mesh.h"
#include "Shader/Shader.h"
#include "Shader/ShaderManager.h"

int main()
{
    try
    {
        App app;
        app.run();
    } catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        GL::Context::Destroy();
        return -1;
    }
    return 0;
}
