#include "render.h"

#include <util/file.h>

#include <stdio.h>
#include <stdlib.h>

GLuint compile_shader(const char *const source, GLint length, GLuint type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, &length);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char error_desc[512];
        glGetShaderInfoLog(shader, 512, nullptr, error_desc);
        fprintf(stderr, "ERROR:SHADER:COMPILE %s\n", error_desc);
        fprintf(stderr, "%s\n", source);

        return 0;
    }

    return shader;
}


int setup_shaders(GLuint *shader_program) {
    // Vertex shader
    char* shader_v = (char*) malloc(512);
    char* shader_f = (char*) malloc(512);

    GLint vbytes; // Bytes of vertex shader
    GLint fbytes; // Bytes of frag   shader

    GLuint shf; // Handle to a fragment shader
    GLuint shv; // Handle to a vertex shader
    GLuint program = 0; // Handle to a shader program

    int status;
    {
        status = get_resource("shader/default.vert", shader_v, vbytes);
        if (status) goto OUT;

        status = get_resource("shader/default.frag", shader_f, fbytes);
        if (status) goto OUT;
    }
    shf = compile_shader(shader_f, fbytes, GL_FRAGMENT_SHADER);
    if (!shf) { status = -5; goto OUT; }
    shv = compile_shader(shader_v, vbytes, GL_VERTEX_SHADER);
    if (!shv) { status = -6; goto OUT; }

    program = glCreateProgram();
    glAttachShader(program, shv);
    glAttachShader(program, shf);
    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        fprintf(stderr, "ERROR:SHADER:LINK %s\n", infoLog);
    }

    glUseProgram(program);

    // Goto clean
OUT:
    free(shader_v);
    free(shader_f);

    *shader_program = program;

    return status;
}
