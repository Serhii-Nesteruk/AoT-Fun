#pragma once

#include <string>
#include "GLDependencies.h"

class Texture2D {
public:
    Texture2D() = default;
    explicit Texture2D(const std::string& path, bool flipY = true);

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    Texture2D(Texture2D&& other) noexcept;
    Texture2D& operator=(Texture2D&& other) noexcept;

    ~Texture2D();

    void Bind(int slot = 0) const;

    GLuint Id() const { return _id; }
    int Width() const { return _w; }
    int Height() const { return _h; }

private:
    void Destroy();

    GLuint _id = 0;
    int _w = 0, _h = 0, _channels = 0;
};