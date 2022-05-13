#pragma once

#include <glm/vec3.hpp>

struct Mesh {
    glm::vec3 * __restrict verticies = nullptr;
    int       * __restrict indicies  = nullptr;
    int num_verticies   = 0;
    int num_indicies    = 0;

    Mesh() = default;
    Mesh (int num_verticies, int num_indicies, void * __restrict verticies_store, void * __restrict indicies_store)
    : num_verticies(num_verticies), num_indicies(num_indicies)
    {
        this->verticies     = (glm::vec3*) verticies_store;
        this->indicies      = (int*) (indicies_store);
    }
    int size_verticies() {
        return num_verticies * sizeof(glm::vec3);
    }
    int size_indicies() {
        return num_indicies * sizeof(int);
    }
};
