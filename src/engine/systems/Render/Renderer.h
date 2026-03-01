#pragma once

#include "Shader/Shader.h"

#include <memory>

#include "RenderTypes.h"

class Renderer {
public:
    void BeginFrame(const FrameContext& context);
    void Submit(DrawCommand cmd);
    void EndFrame();

private:
    void Flush();

    FrameContext _frame{};
    std::vector<DrawCommand> _cmdQueue{};
};
