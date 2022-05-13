#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Triangle {
    glm::vec3 p[3];
};

// Axis aligned bounding box
struct AABB {
    // Position of the top left pixel.
    glm::vec2 position;
    glm::vec2 size;

    AABB(float x, float y, float w, float h) : position(x, y), size(w, h) {}
    AABB() = default;
};
