#include <filesystem>
#include <iostream>

#include "Context.h"
#include "Input/InputSystem.h"
#include "Objects/Mesh.h"
#include "Shader/Shader.h"
#include "Shader/ShaderManager.h"

int main()
{
    try
    {
        using namespace GL;
        using namespace Objects;
        using Color = Style::BaseColors::Color;

        Context::Init();

        Window window({1280, 720}, "AoT");

        Context::MakeContextCurrent(window);
        Context::GladSetup();
        Context::SetUpViewportBasedOnWindow(window);
        Context::SetupCallbacks(window);

        std::vector<std::filesystem::path> shaders = {
                "../assets/shaders/main_vertex.glsl",
                "../assets/shaders/main_fragment.glsl"
        };

        auto shaderProgram = ShaderManager::CreateShaderProgram(shaders);

        struct VertexP { glm::vec3 pos; };

        VertexLayout layoutP{
            .stride = sizeof(VertexP),
            .attribs = {
                { .location = 0, .components = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = offsetof(VertexP, pos) }
            }
        };

        std::vector<VertexP> verts = {
            {{0.5f,0.5f,0.0f}},
            {{ 0.5f,-0.5f,0.0f}},
            {{ -0.5f, -0.5f,0.0f}},
            {{ -0.5f, 0.5f,0.0f}},
        };

        std::vector<unsigned int> indices = {
            0, 1, 3,
            1, 2, 3
        };

        Mesh::Params p;
        p.vertexBytes = ToBytes(verts);
        p.layout = layoutP;
        p.drawMode = Mesh::DrawMode::TRIANGLES;
        p.buffersMode = Mesh::BufferRenderMode::STATIC;
        p.indices = indices;

        Mesh triangle(p);

        Systems::InputSystem::BindAction(
            Systems::Input::Key::Escape_Key,
            Systems::Input::KeyState::Press,
            [&window]()
            {
                glfwSetWindowShouldClose(window.Get(), GLFW_TRUE);
            }
        );

        glDisable(GL_CULL_FACE);
        while (!window.ShouldClose())
        {
            window.Clear(
                Color(
                     Color::FloatToU8(0.2f),
                    Color::FloatToU8(0.3f),
                    Color::FloatToU8(0.3f)
                    ) /* blue-gray */
                );

            Systems::InputSystem::ProcessInput(window);

            shaderProgram.Use();
            triangle.Draw();

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
