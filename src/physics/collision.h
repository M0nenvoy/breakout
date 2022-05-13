#pragma once

#include <glm/vec2.hpp>

enum Collision {
    None    = 0,
    Top     = 1,
    Bottom  = 2,
    Right   = 3,
    Left    = 4,
};

/**
 * Check for the aabb collision
 * @returns From which side A collides with B. Or None if no collision is present.
 */
Collision collision(glm::ivec2 a_position, glm::ivec2 a_size, glm::ivec2 b_position, glm::ivec2 b_size);
