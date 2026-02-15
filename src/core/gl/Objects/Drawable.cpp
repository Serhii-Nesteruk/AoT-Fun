#include "Drawable.h"

GL::Objects::Drawable::Drawable(const Params& params)
    : _vertexBytes(params.vertexBytes),
      _indices(params.indices),
      _buffersMode(params.buffersMode),
      _drawMode(params.drawMode),
      _layout(params.layout)
{
    _vertexCount = (_layout.stride > 0)
        ? static_cast<GLsizei>(_vertexBytes.size() / _layout.stride)
        : 0;

    Drawable::Setup();
}


GL::Objects::Drawable::~Drawable()
{
    DeleteBuffers();
};

void GL::Objects::Drawable::Draw()
{
    glBindVertexArray(_VAO);
    if (_indices.size() > 0)
    {
        glDrawElements(static_cast<GLenum>(_drawMode), _indices.size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(static_cast<GLenum>(_drawMode), 0, _vertexCount);
    }
    // glBindVertexArray(0);
}

void GL::Objects::Drawable::Setup()
{
    GenerateBuffers();
    SetupBuffers();
}

void GL::Objects::Drawable::GenerateBuffers()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);
}

void GL::Objects::Drawable::DeleteBuffers()
{
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
}

void GL::Objects::Drawable::SetupBuffers()
{
    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 _vertexBytes.size(),
                 _vertexBytes.data(),
                 static_cast<GLenum>(_buffersMode));

    if (!_indices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     _indices.size() * sizeof(unsigned int),
                     _indices.data(),
                     static_cast<GLenum>(_buffersMode));
    }

    for (const auto& a : _layout.attribs)
    {
        glEnableVertexAttribArray(a.location);
        glVertexAttribPointer(
            a.location,
            a.components,
            a.type,
            a.normalized,
            static_cast<GLsizei>(_layout.stride),
            reinterpret_cast<void*>(a.offset)
        );
    }

    glBindVertexArray(0);
}

