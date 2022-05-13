#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* This structure is pretty much a namespace of mnemonics to opengl functions.
 * Because I kinda struggle to remember them.
 */
struct VBO {
    GLuint handle = 0;

    VBO() = default;
    VBO(GLuint handle) : handle(handle) { }
    /* Bind the buffer. Don't forget to glGenBuffers the handle before
     * calling this
     */
    void bind() {
        glBindBuffer(GL_ARRAY_BUFFER, this->handle);
    }

    /* Buffer the data. Don't forget to bind() beforehand.
     * @param data Pointer to the data.
     * @param data_size Size in bytes of the data to buffer.
     */
    void buffer(void* data, int data_size, GLuint draw_mode) {
        glBufferData(GL_ARRAY_BUFFER, data_size, data, draw_mode);
    }

    /* Setup the attrib pointer to the layout_id. Enable layout_id
     */
    void point(int layout_id, int component_size, GLuint component_type, int stride, long offset) {
        glVertexAttribPointer(layout_id,
                              component_size,
                              component_type,
                              GL_FALSE,
                              stride,
                              (void*) offset);

        glEnableVertexAttribArray(layout_id);
    }
};
