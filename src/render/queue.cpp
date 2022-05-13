#include "queue.h"

#include <setup_opengl.h>

#include <string.h>

void gen_rectangle_verticies(
        float x,
        float y,
        float w,
        float h,
        float window_w,
        float window_h,
        glm::vec3* ptr) {

    float xcl = to_clip(x,        window_w); // Left    clip position
    float xcr = to_clip(x + w,    window_w); // Right   clip position
    float yct = to_clip(y,        window_h); // Top     clip position
    float ycb = to_clip(y - h,    window_h); // Bottom  clip position

    glm::vec3 verticies[4] = {
        {  xcl,      yct,      0.0f }, // Top left
        {  xcl,      ycb,      0.0f }, // Bottom left
        {  xcr,      ycb,      0.0f }, // Bottom right
        {  xcr,      yct,      0.0f }, // Top right
    };
    memcpy(ptr, verticies, sizeof(verticies));
}

void RenderQueue::add_rectangle(int offset, float x, float y, float width, float height) {
    // Specify indicies
    int of = offset * 4; // Offset for each element of the indicies
    const int new_indicies[6] = {
        0 + of, 1 + of, 2 + of,
        2 + of, 3 + of, 0 + of
    };


    memcpy(indicies + offset * (sizeof(new_indicies) / sizeof(int)),
           &new_indicies,
           sizeof(new_indicies));

    /* Specify verticies */
    glm::vec3 new_verticies[4];

    // Firstly, calculate them:
    gen_rectangle_verticies(x, y, width, height, (float) WIDTH, (float) HEIGHT, new_verticies);

    // Write them to an array       V - Multiply by 12 - amount of floats in four vec3's
    memcpy(this->verticies + offset * 12,
           new_verticies,
           sizeof(new_verticies));
}
