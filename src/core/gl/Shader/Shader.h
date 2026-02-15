#pragma once

#include "GLDependencies.h"

#include <stdexcept>
#include <vector>
#include <string>
#include <filesystem>

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
        void SetSource(const std::string& source);
        void Compile();
        void Destroy();

        static void CheckCompileErrors(GLuint shader, const std::string& type);

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
        static ShaderType DetectType(const std::filesystem::__cxx11::path& p)
        {
            const auto s = p.stem().string(); // "main_vertex", "main_fragment"
            if (s.find("vert") != std::string::npos) return ShaderType::VERTEX;
            if (s.find("frag") != std::string::npos) return ShaderType::FRAGMENT;
            throw std::runtime_error("Can't detect shader type from filename: " + p.string());
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
            _source = {};

            return tmp;
        }

    private:
        GLuint _index = NullObject;
        bool _isCompiled = false;
        // const GLchar* _source = nullptr;
        std::string _source{};
        ShaderType _type = ShaderType::VERTEX;
    };

    class ShaderProgram
    {
    public:
        ShaderProgram() = default;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram(ShaderProgram&& other) noexcept;
        ShaderProgram& operator=(ShaderProgram&& other) noexcept;
        ~ShaderProgram();

        void Create();
        void Attach(GLuint shaderIdx);
        void Link();
        void Use() const;

        [[nodiscard]] bool checkIfAttached(GLuint shaderIdx) const;

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
        
        void setBool(const std::string& name, bool value) const
        {
            glUniform1i(glGetUniformLocation(_program, name.c_str()), (int)value);
        }

        void setInt(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(_program, name.c_str()), value);
        }

        void setFloat(const std::string& name, float value) const
        {
            glUniform1f(glGetUniformLocation(_program, name.c_str()), value);
        }

        void setVec2(const std::string& name, const glm::vec2& value) const
        {
            glUniform2fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
        }

        void setVec2(const std::string& name, float x, float y) const
        {
            glUniform2f(glGetUniformLocation(_program, name.c_str()), x, y);
        }

        void setVec3(const std::string& name, const glm::vec3& value) const
        {
            glUniform3fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
        }

        void setVec3(const std::string& name, float x, float y, float z) const
        {
            glUniform3f(glGetUniformLocation(_program, name.c_str()), x, y, z);
        }

        void setVec4(const std::string& name, const glm::vec4& value) const
        {
            glUniform4fv(glGetUniformLocation(_program, name.c_str()), 1, &value[0]);
        }

        void setVec4(const std::string& name, float x, float y, float z, float w)
        {
            glUniform4f(glGetUniformLocation(_program, name.c_str()), x, y, z, w);
        }

        void setMat2(const std::string& name, const glm::mat2& mat) const
        {
            glUniformMatrix2fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat3(const std::string& name, const glm::mat3& mat) const
        {
            glUniformMatrix3fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat4(const std::string& name, const glm::mat4& mat) const
        {
            glUniformMatrix4fv(glGetUniformLocation(_program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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
