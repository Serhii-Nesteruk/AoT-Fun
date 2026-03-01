#pragma once
#include "Shape2D.h"

class LineShape : public Shape2D {
public:
    LineShape(glm::vec3 position,
              glm::vec2 fromLocal,
              glm::vec2 toLocal,
              const Color& color = Style::BaseColors::WHITE)
        : Shape2D(position, glm::vec3{1.0f, 1.0f, 0.0f}, color)
    {
        Geometry g;
        g.vertices = CoreUtils::MakeLineVerts_PT(fromLocal, toLocal);
        g.indices = {};
        g.drawMode = Mesh::DrawMode::LINES;
        SetGeometry(g);
    }
};