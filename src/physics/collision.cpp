#include "collision.h"

Collision collision(glm::ivec2 a_position, glm::ivec2 a_size, glm::ivec2 b_position, glm::ivec2 b_size) {

    // Leftmost point of A is 'lefter' then rightest point of B. Non-positive if penetrates
    int left_penetration   = ( a_position.x - (b_position.x + b_size.x) );

    // Rightmost point of A is 'righter' then leftmost point of B. Non-positive if penetrates
    int right_penetration  = ( b_position.x - (a_position.x + a_size.x) );

    // Highest point of A is higher then lowest point of B. Non-positive if penetrates
    int bottom_penetration = ( (b_position.y - b_size.y) - a_position.y );

    // Lowest point of A is lower then the highest point of B. Non-positive if penetrates
    int top_penetration    = ( (a_position.y - a_size.y) - b_position.y );

    int collision = ( left_penetration <= 0 && right_penetration <= 0 )
                    &&
                    ( top_penetration <= 0 && bottom_penetration <= 0 );
    if (!collision) {
        return Collision::None;
    }
    // Make an array
    int penetrations[4];

    // Feel heavily relying on the strict organisation of enum
    //                         V - Substract 1 to account that the first element in an enum in Collision::None
    penetrations[Collision::Top-1]      = top_penetration;
    penetrations[Collision::Bottom-1]   = bottom_penetration;
    penetrations[Collision::Right-1]    = right_penetration;
    penetrations[Collision::Left-1]     = left_penetration;

    // Find the max element
    int max_index = 0;
    int max = penetrations[max_index];
    for (int i = 1; i < 4; i++) {
        if (max < penetrations[i]) {
            max = penetrations[i];
            max_index = i;
        }
    }
    return (Collision) (max_index + 1);
}
