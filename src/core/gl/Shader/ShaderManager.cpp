#include "ShaderManager.h"

#include <fstream>
#include <iostream>

#include <algorithm>

std::string GL::ShaderManager::loadSourceCodeFromFile(const std::filesystem::path& path)
{
    if (path.extension() != ".glsl")
    {
        throw std::runtime_error("Failed to load shader source code. The source file should have .glsl extension");
    }

    std::string code;
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    shaderFile.open(path.string());

    std::stringstream shaderStream;

    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}
GL::ShaderProgram GL::ShaderManager::CreateShaderProgram(const ListOfPaths& shaders)
{
    ShaderProgram program;
    program.Create();

    std::vector<Shader::ShaderType> attachedTypes;

    for (const auto& sh : shaders)
    {
        auto src  = loadSourceCodeFromFile(sh);
        auto type = Shader::DetectType(sh);

        const bool already =
            std::find(attachedTypes.begin(), attachedTypes.end(), type) != attachedTypes.end();

        if (already)
            continue;

        Shader shader;
        shader.Create(type);
        shader.SetSource(src);
        shader.Compile();

        program.Attach(shader.Release());
        attachedTypes.push_back(type);
    }

    program.Link();
    return program;
}
