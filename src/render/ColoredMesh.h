#pragma once

#include "mesh.h"

#include <glm/vec2.hpp>

struct ColoredMesh {
    char * memory_pool;
    Mesh positions;
    glm::vec3 * colors;
    glm::vec2 * uv;

    int pos_verticies;

    int size_uv() {
        return sizeof(glm::vec2) * pos_verticies;
    }
    int size_pos() {
        return sizeof(glm::vec3) * pos_verticies;
    }
    int size_colors() {
        return sizeof(glm::vec3) * pos_verticies;
    }

    ColoredMesh(int pos_verticies, int pos_indicies, int color_verticies)
    : pos_verticies(pos_verticies) {
        /*
        int pos_ind_size   = sizeof(int) * pos_indicies;
        int pos_ver_size   = sizeof(glm::vec3) * pos_verticies;
        int color_ver_size = sizeof(glm::vec3) * color_verticies;
        int uv_ver_size    = sizeof(glm::vec2) * pos_verticies;
        */
        int pos_ind_size    = sizeof(int) * pos_indicies;
        int pos_ver_size    = size_pos();
        int color_ver_size  = size_colors();
        int uv_ver_size     = size_uv();

        int memory_size = pos_ind_size + pos_ver_size + color_ver_size + uv_ver_size;
        memory_pool = new char[memory_size];

        char* pos_ver_store     = memory_pool;
        char* color_ver_store   = pos_ver_store     + pos_ver_size;
        char* uv_ver_store      = color_ver_store   + color_ver_size;
        char* pos_ind_store     = uv_ver_store      + uv_ver_size;

        this->positions = Mesh(pos_verticies, pos_indicies, pos_ver_store, pos_ind_store);
        this->colors    = (glm::vec3*) color_ver_store;
        this->uv        = (glm::vec2*) uv_ver_store;
    }

    ~ColoredMesh() {
        delete [] memory_pool;
    }
};
