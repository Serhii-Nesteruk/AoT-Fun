#include <iostream>

#include "Context.h"
#include "Input/InputSystem.h"
#include "Objects/Drawable.h"
#include "Shader/Shader.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

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

        // Shaders
        Shader vertexShader;
        vertexShader.Create(Shader::ShaderType::VERTEX);
        vertexShader.SetSource(vertexShaderSource);
        vertexShader.Compile();

        Shader fragmentShader;
        fragmentShader.Create(Shader::ShaderType::FRAGMENT);
        fragmentShader.SetSource(fragmentShaderSource);
        fragmentShader.Compile();

        // link shaders
        ShaderProgram shaderProgram;
        shaderProgram.Create();
        shaderProgram.Attach(vertexShader.GetIndex());
        shaderProgram.Attach(fragmentShader.GetIndex());
        shaderProgram.Link();

        struct VertexP { glm::vec3 pos; };

        VertexLayout layoutP{
            .stride = sizeof(VertexP),
            .attribs = {
                { .location = 0, .components = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = offsetof(VertexP, pos) }
            }
        };

        std::vector<VertexP> verts = {
            {{-0.5f,-0.5f,0.0f}},
            {{ 0.5f,-0.5f,0.0f}},
            {{ 0.0f, 0.5f,0.0f}},
        };

        Drawable::Params p;
        p.vertexBytes = ToBytes(verts);
        p.layout = layoutP;
        p.drawMode = Drawable::DrawMode::TRIANGLES;
        p.buffersMode = Drawable::BufferRenderMode::STATIC;

        Drawable triangle(p);

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
