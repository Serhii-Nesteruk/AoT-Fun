#pragma once
#include "Shape2D.h"

class CircleShape : public Shape2D {
public:
    CircleShape(glm::vec3 position,
                float radius,
                int segments = 32,
                const Color& color = Style::BaseColors::WHITE)
        : Shape2D(position, glm::vec3{radius * 2.0f, radius * 2.0f, 0.0f}, color)
    {
        Geometry g;
        g.vertices = CoreUtils::MakeCircleVerts_TopLeft_PT(radius, segments);
        g.indices = {};
        g.drawMode = Mesh::DrawMode::TRIANGLE_FAN;
        SetGeometry(g);
    }
};