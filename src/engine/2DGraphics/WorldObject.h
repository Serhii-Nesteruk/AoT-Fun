#pragma once

#include "GLDependencies.h"
#include "Objects/Mesh.h"

namespace CoreUtils
{
    struct VertexP;
}

struct Transform
{
    Transform() : position(0.0f), size(1.0f) {};
    Transform(glm::vec3 pos, glm::vec3 s)
            : position(pos), size(s) {}

    glm::vec3 position;
    glm::vec3 size;
    // glm::quat rotation{};
};

class IWorldObject {
public:
    IWorldObject(glm::vec3 position, glm::vec3 size)
        : _transform(position, size) {};
    virtual ~IWorldObject() = default;

    virtual void Draw(GLuint shaderProgramId) = 0; // TODO: temporary requires shader program id
    virtual void Move(GLuint shaderProgramId, glm::vec3 offset) = 0;

protected:
    std::vector<CoreUtils::VertexP> _vertices{};
    std::unique_ptr<GL::Objects::Mesh> _mesh;
    Transform _transform{};

    static std::vector<unsigned int> _indices;
};

