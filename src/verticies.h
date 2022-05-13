#include "linked_list.h"

#include <stdlib.h>
#include <string.h>

#include <glm/vec3.hpp>

#include <util/file.h>
#include <util/data_types.h>

void setup_verticies(Node<Triangle> *triangle_root, int& number_triangles) {
    // Read triangles from file
    float dest[128];
    int floats_read = read_vertecies("vertecies.txt", dest);
    if (floats_read <= 0) { // Error
        fprintf(stderr, "read_vertecies() failed (%d)\n", floats_read);
        exit(EXIT_FAILURE);
    }

    // How many triangles can we make out of read floats? Each triangle
    // needs 9 float values.
    number_triangles = floats_read / 9;

    if (number_triangles == 0) {
        fprintf(stderr, "Not enough data to create any triangles (only %d floats)\n", floats_read);
    }
    for (int i = 0; i < number_triangles; i++) {
        Triangle triangle;
        memcpy(&triangle, dest + i * sizeof(Triangle) / sizeof(float), sizeof(Triangle));
        triangle_root->append(triangle);
    }
}
