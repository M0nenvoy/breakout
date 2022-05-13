#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <iostream>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include "util/file.h"
#include "util/data_types.h"
#include "util/color.h"

#include "render/render.h"
#include "render/mesh.h"
#include "render/vbo.h"

#include "setup_opengl.h"
#include "input.h"

#include "physics/physics.h"

#include "game/world.h"
#include "game/game_util.h"


Resource RESOURCE;

GLFWwindow* window;


static glm::vec3 BG_COLOR = hex2vec(0xE3D8F1);

int terminate(int status) {
    glfwTerminate();
    return status;
}

void render(int VAO, int elements) {
    glClearColor(BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, nullptr);
}


void fetch_errors() {
    fputs("Fetching errors... ", stderr);
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "(%x), ", err);
    }
    fprintf(stderr, "\n");
}

// Update window's viewport after resizing
void resize_callback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
}


// Supply the path to the 'resources' folder via command line
// arguments.
int main(int argc, char **argv) {
    if (argc < 2) {
        fputs("Usage: app <path/to/the/resource_dir>\n", stderr);
        return -1;
    }

    // Save resource dir to a static storage.
    {
        int bytes = strlen(argv[1]); // Bytes used by an argument ( including the '\0' )

        // Check if the user added the '/' at the end
        if (argv[1][bytes - 1] != '/') {
            argv[1][bytes + 0] = '/';
            argv[1][bytes + 1] = 0;

            bytes++;
        }
        RESOURCE.BYTES = bytes;
        memcpy(RESOURCE.DIR, argv[1], bytes);
    }
    int status = setup_opengl(window);
    if (status) return terminate(status);

    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetKeyCallback(window, key_callback);


    GLuint VAOhandle;
    glGenVertexArrays(1, &VAOhandle);
    glBindVertexArray(VAOhandle);

    GLuint VBOhandle, EBOhandle;
    glGenBuffers(1, &VBOhandle);
    glGenBuffers(1, &EBOhandle);

    std::list<AABB> paddles;
    gen_paddles(paddles, HEIGHT - 10, 15, 20, 4, 6, WIDTH, HEIGHT / 2 - 100);


    int player_width = 100;
    float player_height = 10;
    AABB player = { (float)((WIDTH - player_width) / 2), 50, (float)player_width, player_height };
    AABB ball   = { 300, 100, 10,  10 };

    // Create the world
    GameWorld world = GameWorld(std::move(paddles), player, ball);
    world.ball_velocity = glm::vec2(100);
    world.update_mesh();

    ColoredMesh * colored_mesh = world.mesh;
    Mesh positions = colored_mesh->positions;

    // Setup VBO
    VBO vbo = VBO(VBOhandle);
    vbo.bind();

    vbo.point(0, 3, GL_FLOAT, sizeof(float) * 3, 0);                            // Point to positions
    vbo.point(1, 3, GL_FLOAT, sizeof(float) * 3, positions.size_verticies());   // Point to colors
    vbo.point(2, 2, GL_FLOAT, sizeof(float) * 2, positions.size_verticies() + colored_mesh->size_colors());
    vbo.buffer(positions.verticies, colored_mesh->size_uv() + colored_mesh->size_colors() + colored_mesh->size_pos(), GL_STATIC_DRAW);

    // Setup EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOhandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, positions.size_indicies(), positions.indicies, GL_STATIC_DRAW);

    // Setup shader
    GLuint shader_program;
    status = setup_shaders(&shader_program);
    if (status) return terminate(status);
    glUseProgram(shader_program);

    fetch_errors();

    float time0 = glfwGetTime();
    float last_time = time0;

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        float current_time = glfwGetTime();
        float delta_time = current_time - last_time;
        last_time = current_time;

        vbo.buffer(positions.verticies, colored_mesh->size_uv() + colored_mesh->size_colors() + colored_mesh->size_pos(), GL_DYNAMIC_DRAW);
        vbo.bind();
        render(VAOhandle, world.paddles.size() * 6 + 12);

        constexpr int SPEED = 300;
        world.player_velocity.x = INPUT.rdir * SPEED;
        world.update_physics(delta_time);
        world.update_mesh();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return terminate(0);
}
