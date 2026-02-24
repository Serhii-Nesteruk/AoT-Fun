#pragma once

#include "GLDependencies.h"

class IWorldObject {
public:
    virtual ~IWorldObject() {};

    virtual void Draw(GLuint shaderProgramId) = 0;
    virtual void Move(GLuint shaderProgramId, glm::vec3 offset) = 0;
};

