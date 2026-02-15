#pragma once

#include <vector>

#include "GLDependencies.h"

namespace GL
{
    static constexpr GLuint NullObject = 0;

    class Shader
    {
    public:
        enum class ShaderType : GLenum
        {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
        };

        Shader() = default;
        explicit Shader(GLenum type);
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;
        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;
        ~Shader();

        void Create(ShaderType type);
        void SetSource(const char* source);
        void Compile();
        void Destroy();

        [[nodiscard]] GLuint GetIndex() const
        {
            return _index;
        }

        [[nodiscard]] bool isCompiled() const
        {
            return _isCompiled;
        }

        [[nodiscard]] bool isCreated() const
        {
            return _index != NullObject;
        }

        [[nodiscard]]
        static GLboolean isShader(GLuint index)
        {
            return glIsShader(index);
        }

        [[nodiscard]]
        ShaderType GetType() const
        {
            return _type;
        }

        GLuint Release()
        {
            GLuint tmp = _index;

            _index = NullObject;
            _isCompiled = false;
            _source = nullptr;

            return tmp;
        }

    private:
        GLuint _index = NullObject;
        bool _isCompiled = false;
        const GLchar* _source = nullptr;
        ShaderType _type = ShaderType::VERTEX;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram() = default;
        ~ShaderProgram();

        void Create();
        void Attach(GLuint shaderIdx);
        void Link();
        void Use() const;

        [[nodiscard]] bool isAttached() const
        {
            return _isAttached;
        }
        [[nodiscard]] bool isLinked() const
        {
            return _isLinked;
        }
        [[nodiscard]] bool isCreated() const
        {
            return _isCreated;
        }

    private:
        void DeleteShaders();

        [[nodiscard]] bool isShaderValid(GLuint index) const;

    private:
        std::vector<GLuint> _shaders{};
        GLuint _program = NullObject;
        bool _isAttached = false, _isLinked = false, _isCreated = false;
    };
}
