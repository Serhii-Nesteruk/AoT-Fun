#include "Shader.h"

#include <iostream>
#include <stdexcept>

GL::ShaderProgram::~ShaderProgram()
{
    if (_program != NullObject)
    {
        glDeleteProgram(_program);
    }
}

void GL::ShaderProgram::Create()
{
    if (_program != NullObject)
    {
        glDeleteProgram(_program);
        _program = NullObject;
    }

    _program = glCreateProgram();
    if (_program == NullObject)
    {
        throw std::runtime_error("ShaderProgram::Create(): glCreateProgram failed");
    }

    _isCreated = true;
}

void GL::ShaderProgram::Attach(GLuint shaderIdx)
{
    if (!isCreated())
    {
        throw std::runtime_error("ShaderProgram::Attach(): Program is not created");
    }

    if (!isShaderValid(shaderIdx))
    {
        throw std::invalid_argument("ShaderProgram::Attach(): shader is null");
    }

    glAttachShader(_program, shaderIdx);
    _shaders.push_back(shaderIdx);
    _isAttached = true;
}

void GL::ShaderProgram::Link()
{
    if (!isCreated())
    {
        throw std::runtime_error("ShaderProgram::Link(): Program is not created");
    }

    if (!isAttached())
    {
        throw std::runtime_error("ShaderProgram::Link(): No shader was attached");
    }

    glLinkProgram(_program);

    GLint success = 0;
    glGetProgramiv(_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GL::Shader::CheckCompileErrors(_program, "PROGRAM");
        throw std::runtime_error("ShaderProgram::Link(): link failed");
    }

    _isLinked = true;

    DeleteShaders();
}

void GL::ShaderProgram::Use() const
{
    if (!isCreated())
    {
        throw std::runtime_error("ShaderProgram::Use(): Program is not created");
    }

    if (!isLinked())
    {
        throw std::runtime_error("ShaderProgram::Use(): Program should be linked");
    }

    glUseProgram(_program);
}

void GL::ShaderProgram::DeleteShaders()
{
    for (auto shader : _shaders)
    {
        glDeleteShader(shader);
    }
    _shaders.clear();
}

bool GL::ShaderProgram::isShaderValid(GLuint index) const
{
    return index != NullObject && Shader::isShader(index);
}

GL::Shader::Shader(GLenum type)
    : _index(glCreateShader(type))
    , _type(static_cast<ShaderType>(type))
{
}

GL::Shader::Shader(Shader&& other) noexcept
{
    _index = other._index;
    _type = other._type;
    _isCompiled = other._isCompiled;
    _source = other._source;

    other._source = nullptr;
    other._isCompiled = false;
    other._index = NullObject;
}

GL::Shader& GL::Shader::operator=(Shader&& other) noexcept
{
    if (this != &other)
    {
        Destroy();
        _index = other._index;
        _type = other._type;
        _isCompiled = other._isCompiled;
        _source = other._source;

        other._source = nullptr;
        other._isCompiled = false;
        other._index = NullObject;
    }
    return *this;
}

GL::Shader::~Shader()
{
    Destroy();
}

void GL::Shader::Create(ShaderType type)
{
    Destroy();
    _type = type;
    _index = glCreateShader(static_cast<GLenum>(type));
}

void GL::Shader::SetSource(const GLchar* source)
{
    _source = source;
}

void GL::Shader::Compile()
{
    if (!isCreated())
    {
        throw std::runtime_error("GL::Shader::Compile(): Shader is not created");
    }
    if (!_source)
    {
        throw std::runtime_error("GL::Shader::Compile(): Source is empty");
    }
    if (isCompiled())
    {
        return;
    }

    glShaderSource(_index, 1, &_source, nullptr);
    glCompileShader(_index);

    _isCompiled = true;
}

void GL::Shader::CheckCompileErrors(GLuint shader, const std::string& type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}


void GL::Shader::Destroy()
{
    if (_index != NullObject)
    {
        glDeleteShader(_index);
        _index = NullObject;
        _isCompiled = false;
        _source = nullptr;
    }
}
