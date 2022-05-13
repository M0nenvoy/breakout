#pragma once

#include <linked_list.h>
#include <util/data_types.h>

#include <glm/vec2.hpp>
#include <list>

void physics_update(std::list<AABB> & paddles,
                    AABB & ball,
                    AABB & player,
                    glm::vec2 & ball_velocity,
                    glm::vec2 player_velocity,
                    float delta_time);
