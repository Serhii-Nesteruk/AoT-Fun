#include "Utils.h"

namespace CoreUtils
{
    std::vector<VertexP> MakeRectVerts_TopLeft(glm::vec2 topLeft, float w, float h, float z)
    {
        float x0 = topLeft.x;
        float y0 = topLeft.y;
        float x1 = topLeft.x + w;
        float y1 = topLeft.y - h;

        return {
                        {{ x1, y0, z }}, // 0 top-right
                        {{ x1, y1, z }}, // 1 bottom-right
                        {{ x0, y1, z }}, // 2 bottom-left
                        {{ x0, y0, z }}, // 3 top-left
                    };
    }
}