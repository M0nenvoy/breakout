#pragma once

#include <GL/glew.h>

#include "world.h"
#include <render/vbo.h>

struct WorldRenderer {
    VBO vbo;
    unsigned int EBOhandle;
    int pool_size;
    char * memory_pool;

    WorldRenderer(int pool_size) : pool_size(pool_size), memory_pool(new char[pool_size]) {
        // Setup the VBO
        unsigned int VBOhandle;
        glGenBuffers(1, &VBOhandle);
        vbo = VBO(VBOhandle);
        vbo.bind();
        vbo.point(0, 3, GL_FLOAT, sizeof(float) * 3, 0);

        // Setup the EBO
        glGenBuffers(1, &EBOhandle);
    }

    void sync_data_size(GameWorld * world) {
        int world_data_size = world->mesh->num_verticies * sizeof(float) * 3
                            + world->mesh->num_indicies * sizeof(int);

        assert(pool_size > world_data_size * 2);
        vbo.bind();
        vbo.point(1, 3, GL_FLOAT, sizeof(float) * 3, world->mesh->num_verticies * sizeof(float) * 3);
    }
    void sync_buffer(GameWorld * world) {
        int world_data_size = world->mesh->num_verticies * sizeof(float) * 3
                            + world->mesh->num_indicies * sizeof(int)
                            + world->colors.size() * sizeof(float) * 3;
        vbo.bind();
    }

    void sync(GameWorld * world) {
    }

    ~WorldRenderer() {
        delete [] memory_pool;
    }
};
