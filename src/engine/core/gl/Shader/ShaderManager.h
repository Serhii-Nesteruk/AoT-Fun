#pragma onc
#include <filesystem>
#include <string>

#include "Shader.h"

namespace GL
{
    class ShaderManager final
    {
    public:
        using path = std::filesystem::path;
        using ListOfPaths = std::vector<path>;

        ShaderManager() = default;

        [[nodiscard]]
        static std::string loadSourceCodeFromFile(const path& path);

        [[nodiscard]]
        static ShaderProgram CreateShaderProgram(const ListOfPaths& shaders);

    private:

    };
}
