#pragma once

#include <glm/vec3.hpp>

constexpr int RMASK = 0x00FF0000;
constexpr int GMASK = 0x0000FF00;
constexpr int BMASK = 0x000000FF;

/// Convert the hexidecimal RGB representation of the color to the
/// vector one.
inline constexpr glm::vec3 hex2vec(int hex) {
    return {
       ((hex & RMASK) >> 16) / 255.0,
       ((hex & GMASK) >>  8) / 255.0,
       ((hex & BMASK) >>  0) / 255.0,
    };
}
