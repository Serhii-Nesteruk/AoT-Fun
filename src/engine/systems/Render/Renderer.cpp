#include "Renderer.h"
#include <algorithm>
#include "Shader/Shader.h"
#include "Objects/Mesh.h"

static std::uint64_t MakeSortKey(const DrawCommand& c)
{
    auto p = reinterpret_cast<std::uintptr_t>(c.material.program);
    return static_cast<std::uint64_t>(p);
}

void Renderer::BeginFrame(const FrameContext& frame)
{
    _frame = frame;
    _cmdQueue.clear();
    _cmdQueue.reserve(1024);
}

void Renderer::Submit(DrawCommand cmd)
{
    if (!cmd.mesh || !cmd.material.program) return;
    cmd.sortKey = MakeSortKey(cmd);
    _cmdQueue.push_back(cmd);
}

void Renderer::EndFrame()
{
    Flush();
}

void Renderer::Flush()
{
    std::sort(_cmdQueue.begin(), _cmdQueue.end(),
        [](const DrawCommand& a, const DrawCommand& b)
        {
            return a.sortKey < b.sortKey;
        });

    GL::ShaderProgram* currentProgram = nullptr;

    for (auto& cmd : _cmdQueue)
    {
        if (cmd.material.program != currentProgram)
        {
            currentProgram = cmd.material.program;
            currentProgram->Use();

            currentProgram->SetMat4("uViewProj", _frame.viewProj);
        }

        if (currentProgram)
        {
            currentProgram->SetMat4("uModel", cmd.model);
            currentProgram->SetVec4("uColor", cmd.material.color);
        }

        if (cmd.material.texture)
        {
            cmd.material.texture->Bind(0);
            currentProgram->SetInt("uTexture", 0);
            currentProgram->SetBool("uUseTexture", true);
        }
        else
        {
            currentProgram->SetBool("uUseTexture", false);
        }

        cmd.mesh->Draw();
    }
}