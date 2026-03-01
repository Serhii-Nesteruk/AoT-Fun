#pragma once

#include <cstring>

#include "GLDependencies.h"
#include <glm/vec3.hpp>
#include <vector>

namespace GL::Objects
{
    struct Vertex
    {
        // TODO: implement me
    };

    struct Texture
    {
        // TODO: implement me
    };

    struct VertexAttrib
    {
        GLuint location = 0;
        GLint  components = 3;
        GLenum type = GL_FLOAT;
        GLboolean normalized = GL_FALSE;
        size_t offset = 0;
    };

    struct VertexLayout
    {
        size_t stride = 0;
        std::vector<VertexAttrib> attribs;
    };

    template <class TVertex>
    static std::vector<std::byte> ToBytes(const std::vector<TVertex>& v)
    {
        std::vector<std::byte> out(sizeof(TVertex) * v.size());
        std::memcpy(out.data(), v.data(), out.size());
        return out;
    }

    class Mesh
    {
    public:
        enum class BufferRenderMode : GLenum
        {
            STATIC = GL_STATIC_DRAW,
            DYNAMIC = GL_DYNAMIC_DRAW,
            STREAM = GL_STREAM_DRAW
        };

        enum class DrawMode : GLenum
        {
            POINTS = GL_POINTS,
            LINES = GL_LINES,
            LINE_LOOP = GL_LINE_LOOP,
            TRIANGLES = GL_TRIANGLES,
            TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
            TRIANGLE_FAN = GL_TRIANGLE_FAN,
            LINE_WIDTH = GL_LINE_WIDTH,
            LINE_STRIP = GL_LINE_STRIP,
        };

        struct Params
        {
            std::vector<std::byte> vertexBytes;
            std::vector<unsigned int> indices{};
            VertexLayout layout{};
            BufferRenderMode buffersMode = BufferRenderMode::STATIC;
            DrawMode drawMode = DrawMode::TRIANGLES;
        };


        explicit Mesh(const Params& params);

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&&) = default;
        Mesh& operator=(Mesh&&) = default;

        virtual ~Mesh();

        virtual void Draw() const;
        virtual void Setup();

    protected:
        void GenerateBuffers();
        void DeleteBuffers();
        void SetupBuffers();

        unsigned int _VAO = 0u, _VBO = 0u, _EBO = 0u;

        std::vector<std::byte> _vertexBytes{};
        std::vector<unsigned int> _indices{};
        BufferRenderMode _buffersMode = BufferRenderMode::STATIC;
        DrawMode _drawMode;
        VertexLayout _layout;
        GLsizei _vertexCount = 0;
    };
}
