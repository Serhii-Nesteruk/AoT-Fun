#pragma once

#include <stdexcept>
#include <glm/common.hpp>
#include <glm/vec4.hpp>

/*
    Style::BaseColors

    Small utility for working with RGBA colors in the engine.

    - Input color format:
        RGB : 0..255 (uint8_t)
        A   : 0..1   (float)

    - Internally stored as normalized glm::vec4 (0..1),
      directly usable with OpenGL / shaders / ImGui.

    - Provides:
        * Predefined color constants
        * Color darkening / lightening
        * Color mixing (linear interpolation)
*/
namespace Style::BaseColors
{
    using u8 = std::uint8_t;

    struct Color : glm::vec4
    {
        Color(u8 r, u8 g, u8 b, float a = 1.0f)
            : glm::vec4(NormalizeValues(r, g, b, a))
        {
        }

        /*
            factor = 0.0 -> black
            factor = 1.0 -> original color
         */
        [[nodiscard]]
        static inline Color Darken(const Color& c, float factor = 0.5f)
        {
            factor = glm::clamp(factor, 0.0f, 1.0f);

            return Color(
                ClampU8(static_cast<int>(c.r * 255.0f * factor)),
                ClampU8(static_cast<int>(c.g * 255.0f * factor)),
                ClampU8(static_cast<int>(c.b * 255.0f * factor)),
                c.a
            );
        }

        /*
            factor = 0.0 -> original color
            factor = 1.0 -> white
        */
        [[nodiscard]]
        static inline Color Lighten(const Color& c, float factor = 0.5f)
        {
            factor = glm::clamp(factor, 0.0f, 1.0f);

            return Color(
                ClampU8(static_cast<int>(c.r * 255.0f + (255.0f - c.r * 255.0f) * factor)),
                ClampU8(static_cast<int>(c.g * 255.0f + (255.0f - c.g * 255.0f) * factor)),
                ClampU8(static_cast<int>(c.b * 255.0f + (255.0f - c.b * 255.0f) * factor)),
                c.a
            );
        }

        /*
            t = 0.0 -> a
            t = 1.0 -> b
        */
        [[nodiscard]]
        static inline Color Mix(const Color& a, const Color& b, float t)
        {
            t = glm::clamp(t, 0.0f, 1.0f);

            return Color(
                ClampU8(static_cast<int>(glm::mix(a.r, b.r, t) * 255.0f)),
                ClampU8(static_cast<int>(glm::mix(a.g, b.g, t) * 255.0f)),
                ClampU8(static_cast<int>(glm::mix(a.b, b.b, t) * 255.0f)),
                glm::mix(a.a, b.a, t)
            );
        }

        [[nodiscard]]
        static inline constexpr u8 FloatToU8(float v)
        {
            return static_cast<u8>(v * 255.0f + 0.5f);
        }
    private:
        static constexpr u8 ClampU8(int v)
        {
            return static_cast<u8>(v < 0 ? 0 : (v > 255 ? 255 : v));
        }

        [[nodiscard]]
        inline static glm::vec4 NormalizeValues(
            u8 r, u8 g, u8 b, float a)
        {
            if (r > 255 || g > 255 || b > 255)
                throw std::out_of_range("RGB values must be in range [0, 255]");

            if (a < 0.0f || a > 1.0f)
                throw std::out_of_range("Alpha must be in range [0.0, 1.0]");

            return {
                r / 255.0f,
                g / 255.0f,
                b / 255.0f,
                a
            };
        }
    };

    // BASE COLORS
    inline static const auto RED    = Color(u8{255}, u8{0},   u8{0},   1.0f);
    inline static const auto GREEN  = Color(u8{0},   u8{255}, u8{0},   1.0f);
    inline static const auto BLUE   = Color(u8{0},   u8{0},   u8{255}, 1.0f);
    inline static const auto YELLOW = Color(u8{255}, u8{255}, u8{0},   1.0f);
    inline static const auto WHITE  = Color(u8{255}, u8{255}, u8{255}, 1.0f);
    inline static const auto BLACK  = Color(u8{0},   u8{0},   u8{0},   1.0f);
    inline static const auto PINK   = Color(u8{255}, u8{105}, u8{180}, 1.0f);
    inline static const auto VIOLET = Color(u8{138}, u8{43},  u8{226}, 1.0f);
    inline static const auto ORANGE = Color(u8{255}, u8{165}, u8{0},   1.0f);


    // DARK COLORS
    inline static const auto DARK_RED    = Color(u8{128}, u8{0},   u8{0},   1.0f);
    inline static const auto DARK_GREEN  = Color(u8{0},   u8{128}, u8{0},   1.0f);
    inline static const auto DARK_BLUE   = Color(u8{0},   u8{0},   u8{128}, 1.0f);
    inline static const auto DARK_YELLOW = Color(u8{128}, u8{128}, u8{0},   1.0f);
    inline static const auto GRAY  = Color(u8{192}, u8{192}, u8{192}, 1.0f);
    inline static const auto DARK_PINK   = Color(u8{178}, u8{52},  u8{120}, 1.0f);
    inline static const auto DARK_VIOLET = Color(u8{75},  u8{0},   u8{130}, 1.0f);
    inline static const auto DARK_ORANGE = Color(u8{178}, u8{85},  u8{0},   1.0f);


    // LIGHT COLORS
    inline static const auto LIGHT_RED    = Color(u8{255}, u8{128}, u8{128}, 1.0f);
    inline static const auto LIGHT_GREEN  = Color(u8{128}, u8{255}, u8{128}, 1.0f);
    inline static const auto LIGHT_BLUE   = Color(u8{128}, u8{128}, u8{255}, 1.0f);
    inline static const auto LIGHT_YELLOW = Color(u8{255}, u8{255}, u8{128}, 1.0f);
    inline static const auto LIGHT_WHITE  = Color(u8{255}, u8{255}, u8{255}, 1.0f);
    inline static const auto LIGHT_BLACK  = Color(u8{96},  u8{96},  u8{96},  1.0f);
    inline static const auto LIGHT_PINK   = Color(u8{255}, u8{182}, u8{193}, 1.0f);
    inline static const auto LIGHT_VIOLET = Color(u8{216}, u8{191}, u8{216}, 1.0f);
    inline static const auto LIGHT_ORANGE = Color(u8{255}, u8{200}, u8{120}, 1.0f);
}
