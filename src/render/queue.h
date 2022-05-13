#pragma once

#include <glm/vec3.hpp>

/** Convert pixel coordinates to clip coordinates
 *  @param window_size Size of the window along the converted axis
 */
inline float to_clip(float coord, float window_size) {
    return ( ( coord / window_size ) - 0.5f) * 2.0f;
}

/**
 * Generate the verticies for the rectangle
 * @param x Position x of the top left pixel
 * @param y Position y of the top left pixel
 * @param w Width in pixels
 * @param h Height in pixels
 * @param window_w Window width in pixels
 * @param window_h Window height in pixels
 * @param ptr store generated verticies here
 */
void gen_rectangle_verticies(
        float x,
        float y,
        float w,
        float h,
        float window_w,
        float window_h,
        glm::vec3* ptr);

struct RenderQueue {
    float verticies[512];
    int   indicies [512];

    /** Add a rectangle to a render queue.
     *  Rectangle parameters are defined in pixels and then translated to clip
     *  space via window width and height specified in `setup_opengl.h`
     */
    void add_rectangle(int offset, float x, float y, float width, float height);
    void add_rectangle(int offset, float param[4]) {
        add_rectangle(offset, param[0], param[1], param[2], param[3]);
    }
};
