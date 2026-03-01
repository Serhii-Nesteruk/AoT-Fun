#include "Texture2D.h"
#include <stdexcept>

#include "GLDependencies.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture2D::Texture2D(const std::string& path, bool flipY)
{
    stbi_set_flip_vertically_on_load(flipY ? 1 : 0);

    unsigned char* data = stbi_load(path.c_str(), &_w, &_h, &_channels, 4);
    if (!data) throw std::runtime_error("Texture2D: failed to load: " + path);

    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _w, _h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}

Texture2D::Texture2D(Texture2D&& other) noexcept
{
    *this = std::move(other);
}

Texture2D& Texture2D::operator=(Texture2D&& other) noexcept
{
    if (this == &other) return *this;
    Destroy();
    _id = other._id; other._id = 0;
    _w = other._w; _h = other._h; _channels = other._channels;
    other._w = other._h = other._channels = 0;
    return *this;
}

Texture2D::~Texture2D()
{
    Destroy();
}

void Texture2D::Destroy()
{
    if (_id != 0) {
        glDeleteTextures(1, &_id);
        _id = 0;
    }
}

void Texture2D::Bind(int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _id);
}