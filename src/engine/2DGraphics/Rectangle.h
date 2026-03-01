#pragma once

#include <memory>

#include "GLDependencies.h"
#include "../style/BaseColors.h"
#include "WorldObject.h"

namespace CoreUtils
{
    struct VertexP;
}


class Rectangle : public IWorldObject {
    using Color = Style::BaseColors::Color;
    using Mesh = GL::Objects::Mesh;
    using VertexP = CoreUtils::VertexP;
public:
    explicit Rectangle(glm::vec3 position, glm::vec3 size, const Color& color = Style::BaseColors::WHITE);

    void Draw(GLuint shaderProgramId) override;

    void SetColor(const Color& color);
    void Move(GLuint shaderProgramId, glm::vec3 offset) override;

private:
    [[nodiscard]] std::unique_ptr<Mesh> MakeRectMesh(const GL::Objects::VertexLayout& layoutP) const;
    void Init();

    Color _color;
};
