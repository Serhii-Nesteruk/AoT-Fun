#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include "Window.h"
#include "WorldObject.h"
#include "engine/core/style/BaseColors.h"
#include "Objects/Mesh.h"
#include "Shader/Shader.h"

class App {
    struct VertexP { glm::vec3 pos; };

    using Color = Style::BaseColors::Color;
    using ShaderVec = std::vector<std::filesystem::path>;
    using Vertices = std::vector<VertexP>;

    using Mesh = GL::Objects::Mesh;
public:
    App();
    ~App();

    void run();
private:
    void RunAnimation(float deltaTime);

    void WorldObjectsInit();
    void ContextSetup();
    void AppInit();
    void SetupSystems();
    void Draw();

    std::unique_ptr<GL::Window> _window;
    ShaderVec _shaders{};

    GL::ShaderProgram _shaderProgram;
    Vertices _vertices{};
    std::vector<unsigned int> _indices{};

    std::vector<std::unique_ptr<IWorldObject>> _objects{};

    // delete this test var
    bool moveLeft = false;
};
