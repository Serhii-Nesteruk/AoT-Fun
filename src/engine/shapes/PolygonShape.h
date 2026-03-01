#pragma once
#include "Shape2D.h"

class PolygonShape : public Shape2D {
public:
    PolygonShape(glm::vec3 position,
                 float radius,
                 int sides,
                 const Color& color = Style::BaseColors::WHITE)
        : Shape2D(position, glm::vec3{radius * 2.0f, radius * 2.0f, 0.0f}, color)
    {
        Geometry g;
        g.vertices = CoreUtils::MakeRegularPolygonVerts_TopLeft_PT(radius, sides);
        g.indices = {};
        g.drawMode = Mesh::DrawMode::TRIANGLE_FAN;
        SetGeometry(g);
    }
};