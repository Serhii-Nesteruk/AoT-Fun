#pragma once
#include "Shape2D.h"

class RectangleShape : public Shape2D {
public:
    RectangleShape(glm::vec3 position,
                   glm::vec3 size,
                   const Color& color = Style::BaseColors::WHITE)
        : Shape2D(position, size, color)
    {
        Geometry g;
        g.vertices = CoreUtils::MakeRectVerts_TopLeft_PT(size.x, size.y);
        g.indices  = { 0, 1, 3, 1, 2, 3 };
        SetGeometry(g);
    }
};