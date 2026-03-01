#pragma once
#include "Shape2D.h"

class EllipseShape : public Shape2D {
public:
    EllipseShape(glm::vec3 position,
                 float rx,
                 float ry,
                 int segments = 48,
                 const Color& color = Style::BaseColors::WHITE)
        : Shape2D(position, glm::vec3{rx * 2.0f, ry * 2.0f, 0.0f}, color)
    {
        Geometry g;
        g.vertices = CoreUtils::MakeEllipseVerts_TopLeft_PT(rx, ry, segments);
        g.indices = {};
        g.drawMode = Mesh::DrawMode::TRIANGLE_FAN;
        SetGeometry(g);
    }
};