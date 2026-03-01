#pragma once

#include "GLDependencies.h"
#include "Texture/Texture2D.h"

namespace GL { class ShaderProgram; }
namespace GL::Objects { class Mesh; }

struct Material {
    GL::ShaderProgram* program = nullptr;
    Texture2D* texture = nullptr;
    glm::vec4 color = {1,1,1,1};
};

struct DrawCommand {
    const GL::Objects::Mesh* mesh = nullptr;
    Material material{};
    glm::mat4 model = glm::mat4(1.0f);
    std::uint64_t sortKey = 0;
};

struct FrameContext {
    float dt = 0.0f;
    glm::mat4 viewProj = glm::mat4(1.0f);
};