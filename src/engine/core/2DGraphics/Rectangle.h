#pragma once

#include <memory>

#include "GLDependencies.h"
#include "../style/BaseColors.h"
#include "Objects/Mesh.h"
#include "WorldObject.h"

class Rectangle : public IWorldObject {
    struct VertexP { glm::vec3 pos; };

    using Color = Style::BaseColors::Color;
    using Mesh = GL::Objects::Mesh;
public:
    explicit Rectangle(glm::vec3 position, glm::vec3 size, const Color& color = Style::BaseColors::WHITE);

    void Draw(GLuint shaderProgramId) override;

    void SetColor(const Color& color);
    void Move(GLuint shaderProgramId, glm::vec3 offset) override;

    [[nodiscard]]
    static std::vector<VertexP> MakeRectVerts_TopLeft(glm::vec2 topLeft, float w, float h, float z = 0.0f);

private:
    [[nodiscard]] std::unique_ptr<Mesh> MakeRectMesh(const GL::Objects::VertexLayout& layoutP) const;
    void Init();

    std::unique_ptr<Mesh> _mesh;

    glm::vec3 _position{}, _size{};

    Color _color;

    std::vector<VertexP> _vertices{};
    static std::vector<unsigned int> _indices;
};
