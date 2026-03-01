#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include "Window.h"
#include "WorldObject.h"
#include "engine/core/style/BaseColors.h"
#include "Objects/Mesh.h"
#include "Shader/Shader.h"
#include "Utils.h"

class App {
    using Color = Style::BaseColors::Color;
    using ShaderVec = std::vector<std::filesystem::path>;
    using Vertices = std::vector<CoreUtils::VertexP>;
    using Mesh = GL::Objects::Mesh;
public:
    App();
    ~App();

    void run();
private:
    void WorldObjectsInit();
    void ContextSetup();
    void AppInit();
    void SetupSystems();
    void Draw();
    void CreateRenderContext();
    void CreateWindow();

    Renderer _renderer;
    std::unique_ptr<GL::Window> _window;

    std::unique_ptr<GL::ShaderProgram> _shaderProgram;

    std::vector<std::unique_ptr<IWorldObject>> _objects{};
};
