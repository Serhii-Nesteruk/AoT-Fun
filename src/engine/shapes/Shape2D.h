#pragma once
#include <memory>
#include <vector>

#include "WorldObject.h"
#include "Objects/Mesh.h"
#include "Utils.h"
#include "../style/BaseColors.h"

class Texture2D;

class Shape2D : public IWorldObject {
public:
    using Mesh = GL::Objects::Mesh;
    using Vertex = CoreUtils::VertexPT;
    using Color = Style::BaseColors::Color;

    struct Geometry {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Mesh::DrawMode drawMode = Mesh::DrawMode::TRIANGLES;
        Mesh::BufferRenderMode bufferMode = Mesh::BufferRenderMode::STATIC;
    };

    Shape2D(glm::vec3 position,
            glm::vec3 size,
            const Color& color = Style::BaseColors::WHITE);
    
    void Draw(RenderContext& ctx) override;

    void Move(glm::vec3 offset) override { _transform.position += offset; }

    void SetColor(const Color& c) { _material.color = c; }
    void SetTexture(Texture2D* tex) { _material.texture = tex; }

    void SetGeometry(const Geometry& geom);

protected:
    void InitMeshFromGeometry(const Geometry& geom);

    [[nodiscard]] glm::mat4 MakeModelMatrix() const;

    std::unique_ptr<Mesh> _mesh;
    Geometry _geometry{};
    Material _material{};
};
