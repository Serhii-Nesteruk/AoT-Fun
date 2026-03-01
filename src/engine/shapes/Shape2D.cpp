#include "Shape2D.h"
#include "Shader/Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <stdexcept>

Shape2D::Shape2D(glm::vec3 position, glm::vec3 size, const Color& color)
    : IWorldObject(position, size)
{
    _material.color = color;
}

glm::mat4 Shape2D::MakeModelMatrix() const
{
    glm::mat4 m(1.0f);
    m = glm::translate(m, _transform.position);
    return m;
}

void Shape2D::SetGeometry(const Geometry& geom)
{
    if (geom.vertices.empty())
        throw std::invalid_argument("Shape2D::SetGeometry: vertices empty");

    _geometry = geom;
    InitMeshFromGeometry(_geometry);
}

void Shape2D::InitMeshFromGeometry(const Geometry& geom)
{
    GL::Objects::VertexLayout layout {
        .stride = sizeof(Vertex),
        .attribs = {
            { .location = 0, .components = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = offsetof(Vertex, pos) },
            { .location = 1, .components = 2, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = offsetof(Vertex, uv)  }
        }
    };

    Mesh::Params p;
    p.vertexBytes = GL::Objects::ToBytes(geom.vertices);
    p.indices = geom.indices;
    p.layout = layout;
    p.drawMode = geom.drawMode;
    p.buffersMode = geom.bufferMode;

    _mesh = std::make_unique<Mesh>(p);
}

void Shape2D::Draw(RenderContext& ctx)
{
    if (!_mesh) return;

    DrawCommand cmd;
    cmd.mesh = _mesh.get();
    cmd.material.program = &ctx.shaderProgram;
    cmd.material.color   = _material.color;
    cmd.material.texture = _material.texture;

    cmd.model = MakeModelMatrix();

    ctx.renderer.Submit(cmd);
}