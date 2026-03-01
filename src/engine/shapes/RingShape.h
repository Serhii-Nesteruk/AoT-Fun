#pragma once
#include "Shape2D.h"

class RingShape : public Shape2D {
public:
    RingShape(glm::vec3 position,
              float innerRadius,
              float outerRadius,
              int segments = 64,
              const Color& color = Style::BaseColors::WHITE)
        : Shape2D(position, glm::vec3{outerRadius * 2.0f, outerRadius * 2.0f, 0.0f}, color)
    {
        Geometry g;
        g.vertices = CoreUtils::MakeRingVerts_TopLeft_PT(innerRadius, outerRadius, segments);
        g.indices = {};
        g.drawMode = Mesh::DrawMode::TRIANGLE_STRIP;
        SetGeometry(g);
    }
};