#include "physics.h"
#include "collision.h"
#include "setup_opengl.h"
#include <stdio.h>

#include <list>

void physics_update(std::list<AABB> & paddles,
                    AABB & ball,
                    AABB & player,
                    glm::vec2 & ball_velocity,
                    glm::vec2 player_velocity,
                    float delta_time) {

    // Calculate the actual velocity accounting for delta_time
    glm::vec2 ball_velocity_actual = ball_velocity * delta_time;
    glm::vec2 player_velocity_actual = player_velocity * delta_time;

    // New position of a ball aabb
    ball.position += ball_velocity_actual;

    // New position of a player
    player.position += player_velocity_actual;

    { // Check for a collision with sides of the screen first

    /* Those are all non negative if penetration is present */
    int top_penetration     = ball.position.y  - HEIGHT;
    int bot_penetration     = ball.size.y - ball.position.y;
    int right_penetration   = (ball.position.x + ball.size.x) - WIDTH;
    int left_penetration    = -ball.position.x;

    if (top_penetration >= 0 || bot_penetration >= 0) {
        ball_velocity.y = -ball_velocity.y;
        return;
    }

    if (right_penetration >= 0 || left_penetration >= 0) {
        ball_velocity.x = -ball_velocity.x;
        return;
    }

    } // Screen collision end

    { // Player collision
    Collision collide = collision(ball.position, ball.size, player.position, player.size);
    if (collide) {
        constexpr float velocity_pass_coefficient = 0.25f;
        ball_velocity.y = -ball_velocity.y;
        ball_velocity.x += player_velocity.x * velocity_pass_coefficient;
        return;
    }

    } // Player collision end

    for (auto it = paddles.begin(); it != paddles.end(); it++) { // Paddles collision
        AABB paddle = *it;

        // Check for collision
        Collision collide = collision(ball.position, ball.size, paddle.position, paddle.size);

        // Destroy on collision
        if (collide)
            it = paddles.erase(it);

        switch(collide) {
            case(Collision::Top):       ball_velocity.y = -ball_velocity.y; break;
            case(Collision::Bottom):    ball_velocity.y = -ball_velocity.y; break;
            case(Collision::Right):     ball_velocity.x = -ball_velocity.x; break;
            case(Collision::Left):      ball_velocity.x = -ball_velocity.x; break;
            case(Collision::None):      break;
        }
    }; // Paddles collision end
}
