#pragma once

#include "GLDependencies.h"

#include <filesystem>
#include <memory>
#include <vector>

#include "Window.h"
#include "WorldObject.h"
#include "engine/core/style/BaseColors.h"
#include "Shader/Shader.h"
#include "Utils.h"

class GameTemplate2D {
protected:
    using Color = Style::BaseColors::Color;
    using ShaderVec = std::vector<std::filesystem::path>;

public:
    GameTemplate2D() = default;
    virtual ~GameTemplate2D() = default;

    void Run();

protected:
    virtual void OnInit() {}
    virtual void OnUpdate(float) {}
    virtual void OnRender() {}
    virtual void OnShutdown() {}

    void run();
    void ContextSetup();
    void AppInit();
    void Draw();
    void CreateRenderContext();
    void CreateWindow();
    void Shutdown();

    virtual std::pair<glm::vec2, const char*> GetDefaultWindowParams() const;
    virtual ShaderVec GetDefaultShaders() const;

protected:
    Renderer _renderer;
    std::unique_ptr<GL::Window> _window;
    std::unique_ptr<GL::ShaderProgram> _shaderProgram;
    std::vector<std::unique_ptr<IWorldObject>> _objects{};
};