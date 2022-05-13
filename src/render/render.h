#pragma once

#include <GL/glew.h>

namespace Render {
    GLuint VAOlines();
};

/* Compile a shader from the string `source`
 * Return the shader or 0 on failure
 */
GLuint compile_shader(const char *const source, GLint length, GLuint type);

/* Bind default.vert and default.frag shaders
 * to a shader_program. Don't forget to actually glUseProgram(shader_program)
 * Return the status.
 */
int setup_shaders(GLuint *shader_program);
