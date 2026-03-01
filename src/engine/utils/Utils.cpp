#include "Utils.h"

namespace CoreUtils
{
    std::vector<VertexPT> MakeRectVerts_TopLeft_PT(float w, float h, float z)
    {
        return {
                {{0.f, 0.f, z}, {0.f, 0.f}}, // top-left
                {{w  , 0.f, z}, {1.f, 0.f}}, // top-right
                {{w  , h  , z}, {1.f, 1.f}}, // bottom-right
                {{0.f, h  , z}, {0.f, 1.f}}, // bottom-left
            };
    }

    std::vector<VertexPT> MakeTriVerts_TopLeft_PT(float w, float h, float z)
    {
        // A (0,0), B (w,0), C (0,h)
        return {
                {{0.f, 0.f, z}, {0.f, 0.f}},
                {{w  , 0.f, z}, {1.f, 0.f}},
                {{0.f, h  , z}, {0.f, 1.f}},
            };
    }

     std::vector<VertexPT> MakeCircleVerts_TopLeft_PT(float radius, int segments, float z)
    {
        if (segments < 3) segments = 3;

        const glm::vec2 c{radius, radius};

        std::vector<VertexPT> v;
        v.reserve((size_t)segments + 2);

        v.push_back({{c.x, c.y, z}, {0.5f, 0.5f}});

        for (int i = 0; i <= segments; ++i)
        {
            float a = (2.0f * M_PI) * (float)i / (float)segments;
            float x = c.x + std::cos(a) * radius;
            float y = c.y + std::sin(a) * radius;

            float u = (x / (2.0f * radius));
            float vv = (y / (2.0f * radius));

            v.push_back({{x, y, z}, {u, vv}});
        }

        return v;
    }

    std::vector<VertexPT> MakeEllipseVerts_TopLeft_PT(float rx, float ry, int segments, float z)
    {
        if (segments < 3) segments = 3;

        const glm::vec2 c{rx, ry};

        std::vector<VertexPT> v;
        v.reserve((size_t)segments + 2);

        v.push_back({{c.x, c.y, z}, {0.5f, 0.5f}});

        for (int i = 0; i <= segments; ++i)
        {
            float a = (2.0f * M_PI) * (float)i / (float)segments;
            float x = c.x + std::cos(a) * rx;
            float y = c.y + std::sin(a) * ry;

            float u = x / (2.0f * rx);
            float vv = y / (2.0f * ry);

            v.push_back({{x, y, z}, {u, vv}});
        }

        return v;
    }

    std::vector<VertexPT> MakeRegularPolygonVerts_TopLeft_PT(float radius, int sides, float z)
    {
        if (sides < 3) sides = 3;
        const glm::vec2 c{radius, radius};

        std::vector<VertexPT> v;
        v.reserve((size_t)sides + 2);

        v.push_back({{c.x, c.y, z}, {0.5f, 0.5f}});

        for (int i = 0; i <= sides; ++i)
        {
            float a = (2.0f * M_PI) * (float)i / (float)sides;
            float x = c.x + std::cos(a) * radius;
            float y = c.y + std::sin(a) * radius;

            float u = x / (2.0f * radius);
            float vv = y / (2.0f * radius);

            v.push_back({{x, y, z}, {u, vv}});
        }

        return v;
    }

    std::vector<VertexPT> MakeLineVerts_PT(glm::vec2 from, glm::vec2 to, float z)
    {
        return {
            {{from.x, from.y, z}, {0.f, 0.f}},
            {{to.x,   to.y,   z}, {1.f, 1.f}}
        };
    }

    std::vector<VertexPT> MakeRingVerts_TopLeft_PT(float innerR, float outerR, int segments, float z)
    {
        if (innerR < 0) innerR = 0;
        if (outerR <= innerR) outerR = innerR + 1.0f;
        if (segments < 3) segments = 3;

        const glm::vec2 c{outerR, outerR};

        std::vector<VertexPT> v;
        v.reserve((size_t)(segments + 1) * 2);

        for (int i = 0; i <= segments; ++i)
        {
            float a = (2.0f * M_PI) * (float)i / (float)segments;
            float ca = std::cos(a);
            float sa = std::sin(a);

            glm::vec2 pOuter = c + glm::vec2(ca * outerR, sa * outerR);
            glm::vec2 pInner = c + glm::vec2(ca * innerR, sa * innerR);

            glm::vec2 uvOuter = pOuter / (2.0f * outerR);
            glm::vec2 uvInner = pInner / (2.0f * outerR);

            v.push_back({{pOuter.x, pOuter.y, z}, {uvOuter.x, uvOuter.y}});
            v.push_back({{pInner.x, pInner.y, z}, {uvInner.x, uvInner.y}});
        }

        return v;
    }
}