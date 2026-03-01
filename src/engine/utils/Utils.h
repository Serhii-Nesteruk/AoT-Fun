    #pragma once

    #include "GLDependencies.h"

    #include <vector>

    namespace CoreUtils
    {
        struct VertexP { glm::vec3 pos; };

        [[nodiscard]]
        std::vector<VertexP> MakeRectVerts_TopLeft(glm::vec2 topLeft, float w, float h, float z = 0.0f);

    }