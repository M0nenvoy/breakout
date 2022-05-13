#pragma once

#include <setup_opengl.h>
#include <render/ColoredMesh.h>
#include <util/data_types.h>

#include <list>
#include <string.h>

struct GameWorld {
    ColoredMesh * mesh = nullptr;
    std::list<AABB> paddles;
    std::list<glm::vec3> colors; // Paddle colors
    AABB player;
    AABB ball;
    glm::vec2 ball_velocity     = glm::vec2(0);
    glm::vec2 player_velocity   = glm::vec2(0);

    GameWorld(std::list<AABB> && paddles, AABB player, AABB ball);

    void write_rectangle_to_mesh(int rn /* Rect number */, glm::vec3 verticies[4]);
    void write_aabb_to_mesh(int rn, AABB & aabb);
    void write_color_to_mesh(int cn, glm::vec3 & color);
    void write_uv_to_mesh(int n);

    void update_mesh();
    void update_physics(float delta_time);

    ~GameWorld() {
        delete mesh;
    }
};
