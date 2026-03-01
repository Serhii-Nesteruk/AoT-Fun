#pragma once
#include "Shape2D.h"

class TriangleShape : public Shape2D {
public:
    TriangleShape(glm::vec3 position,
                  glm::vec3 size,
                  const Color& color = Style::BaseColors::WHITE)
        : Shape2D(position, size, color)
    {
        Geometry g;
        g.vertices = CoreUtils::MakeTriVerts_TopLeft_PT(size.x, size.y);
        g.indices  = {};
        SetGeometry(g);
    }
};