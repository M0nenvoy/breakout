#include "world.h"

#include <util/color.h>
#include <render/queue.h>
#include <physics/physics.h>

GameWorld::GameWorld(std::list<AABB> && paddles, AABB player, AABB ball)
        : paddles(paddles), player(player), ball(ball) {

    // Setup the mesh
    int num_indicies    = paddles.size() * 6 + 12;
    int num_verticies   = paddles.size() * 4 + 8;
    mesh = new ColoredMesh(num_verticies, num_indicies, num_verticies);
}

void GameWorld::update_mesh() {
    int rn = 0; // Rect number

    glm::vec3 paddle_clr    = hex2vec(0xDABECA);
    glm::vec3 ball_clr      = hex2vec(0xBF8B85);

    // Append paddles
    for (AABB paddle : paddles) {
        write_aabb_to_mesh(rn, paddle);
        write_color_to_mesh(rn, paddle_clr);
        write_uv_to_mesh(rn);
        rn++;
    }

    // Append ball
    write_aabb_to_mesh(rn, ball);
    write_color_to_mesh(rn, ball_clr);
    write_uv_to_mesh(rn);
    rn++;

    // Append player
    write_aabb_to_mesh(rn, player);
    write_color_to_mesh(rn, ball_clr);
    write_uv_to_mesh(rn);
    rn++;
}
void GameWorld::write_rectangle_to_mesh(int rn, glm::vec3 verticies[4]) {
    // Write verticies
    memcpy(mesh->positions.verticies + 4 * (rn), verticies, sizeof(glm::vec3[4]));

    int offs = rn * 4;

    int indicies[6] = {
        0 + offs,  1 + offs,  2 + offs,
        2 + offs,  3 + offs,  0 + offs
    };

    // Write indicies
    memcpy(mesh->positions.indicies + 6 * (rn), (int*)indicies, sizeof(indicies));
}

void GameWorld::write_color_to_mesh(int cn, glm::vec3 & color) {
    int coffs = 4 * cn;
    memcpy(mesh->colors + coffs + 0, &color, sizeof(color));
    memcpy(mesh->colors + coffs + 1, &color, sizeof(color));
    memcpy(mesh->colors + coffs + 2, &color, sizeof(color));
    memcpy(mesh->colors + coffs + 3, &color, sizeof(color));
}

void GameWorld::write_aabb_to_mesh(int rn, AABB & aabb) {
    glm::vec3 verticies[4];
    gen_rectangle_verticies(aabb.position.x, aabb.position.y,
                            aabb.size.x, aabb.size.y,
                            WIDTH, HEIGHT,
                            verticies);

    write_rectangle_to_mesh(rn, verticies);
}

void GameWorld::write_uv_to_mesh(int n) {
    constexpr float uv[8] = {
        0.0f, 1.0f, // Top left
        0.0f, 0.0f, // Bottom left
        1.0f, 0.0f, // Bottom right
        1.0f, 1.0f, // Top right
    };
    memcpy(mesh->uv + 4 * n, uv, sizeof(uv));
}

void GameWorld::update_physics(float delta_time) {
    physics_update(this->paddles, this->ball, this->player, this->ball_velocity, this->player_velocity, delta_time);
}
