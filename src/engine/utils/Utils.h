#pragma once

#include "GLDependencies.h"

#include <vector>

namespace CoreUtils
{
    struct VertexPT
    {
        glm::vec3 pos;
        glm::vec2 uv;
    };

    [[nodiscard]] std::vector<VertexPT> MakeRectVerts_TopLeft_PT(float w, float h, float z = 0.0f);
    [[nodiscard]] std::vector<VertexPT> MakeTriVerts_TopLeft_PT(float w, float h, float z = 0.0f);
    [[nodiscard]] std::vector<VertexPT> MakeCircleVerts_TopLeft_PT(float radius, int segments, float z = 0.0f);
    [[nodiscard]] std::vector<VertexPT> MakeEllipseVerts_TopLeft_PT(float rx, float ry, int segments, float z = 0.0f);

    [[nodiscard]] std::vector<VertexPT> MakeRegularPolygonVerts_TopLeft_PT(float radius, int sides, float z = 0.0f);

    [[nodiscard]] std::vector<VertexPT> MakeLineVerts_PT(glm::vec2 from, glm::vec2 to, float z = 0.0f);

    [[nodiscard]] std::vector<VertexPT> MakeRingVerts_TopLeft_PT(float innerR, float outerR, int segments, float z = 0.0f);


}
