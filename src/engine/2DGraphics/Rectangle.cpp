#include "Rectangle.h"

#include "Utils.h"
#include "Shader/Shader.h"

std::vector<unsigned int> IWorldObject::_indices = {
    0, 1, 3,
    1, 2, 3
};

Rectangle::Rectangle(glm::vec3 position, glm::vec3 size, const Color& color)
    : IWorldObject(position, size), _color(color)
{
    Init();
}

void Rectangle::Draw(GLuint shaderProgramId)
{
    glUniform4fv(glGetUniformLocation(shaderProgramId, "uColor"), 1, &_color[0]);
    _mesh->Draw();
}

void Rectangle::SetColor(const Color& color)
{
    _color = color;
}

void Rectangle::Move(GLuint shaderProgramId, glm::vec3 offset)
{
    _transform.position += offset;
    glUniform3fv(glGetUniformLocation(shaderProgramId, "uOffset"), 1, &offset[0] );
}

void Rectangle::Init()
{
    _vertices = CoreUtils::MakeRectVerts_TopLeft(_transform.position, _transform.size.x, _transform.size.y);
    GL::Objects::VertexLayout layoutP {
        .stride = sizeof(VertexP),
        .attribs = {
            { .location = 0, .components = 3, .type = GL_FLOAT, .normalized = GL_FALSE, .offset = offsetof(VertexP, pos) }
        }
    };
    _mesh = MakeRectMesh(layoutP);
}

 std::unique_ptr<Rectangle::Mesh> Rectangle::MakeRectMesh(const GL::Objects::VertexLayout& layoutP) const
{
    if (_vertices.empty())
    {
        throw std::runtime_error("Rectangle::MakeRectMesh: Vertices are empty");
    }

    if (_indices.empty())
    {
        throw std::runtime_error("Rectangle::MakeRectMesh: Indices are empty");
    }

    if (layoutP.attribs.empty())
    {
        throw std::invalid_argument("Rectangle::MakeRectMesh: Layout attributes are empty");
    }

    Mesh::Params p;
    p.vertexBytes = GL::Objects::ToBytes(_vertices);
    p.layout = layoutP;
    p.drawMode = Mesh::DrawMode::TRIANGLES;
    p.buffersMode = Mesh::BufferRenderMode::STATIC;
    p.indices = _indices;

    return std::make_unique<Mesh>(p);
}
