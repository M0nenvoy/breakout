#pragma once

#include <util/data_types.h>

struct Paddle {
    AABB aabb = { 10, 10, 10, 10 };
    bool destructable = true;
    Paddle() = default;
    Paddle(AABB aabb, bool destructable) : aabb(aabb), destructable(destructable) {};
};
