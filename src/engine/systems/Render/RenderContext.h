#pragma once
#include "Shader/Shader.h"

class Renderer;

struct RenderContext {
    Renderer& renderer;
    GL::ShaderProgram& shaderProgram;
};
