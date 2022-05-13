#pragma once

#include <util/data_types.h>
#include <list>

void gen_paddles(std::list<AABB> & dest,
                 float top,
                 float padding_v,
                 float padding_h,
                 int rows,
                 int cols,
                 float scr_width,
                 float scr_height) {
    float pad_w = (scr_width  - padding_h) / cols - padding_h;
    float pad_h = (scr_height - padding_v) / rows - padding_v;

    float current_top  = top;
    for (int y = 0; y < rows; y++) {
        float current_left = padding_h;
        for (int i = 0; i < cols; i++) {
            AABB aabb = AABB (current_left, current_top, pad_w, pad_h);
            dest.push_back(aabb);
            current_left += padding_h + pad_w;
        }
        current_top -= (padding_v + pad_h);
    }
}
