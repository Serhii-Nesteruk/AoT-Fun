#pragma once

#include "GLDependencies.h"
#include "../systems/Render/RenderContext.h"
#include "../systems/Render/Renderer.h"
#include "Objects/Mesh.h"

namespace CoreUtils
{
    struct VertexPT;
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

    virtual void Draw(RenderContext& ctx) = 0;
    virtual void Move(glm::vec3 offset) = 0;

    const Transform& GetTransform() const { return _transform; }
    Transform& GetTransform() { return _transform; }
protected:
    std::vector<CoreUtils::VertexPT> _vertices{};
    std::unique_ptr<GL::Objects::Mesh> _mesh;
    Transform _transform{};
};

