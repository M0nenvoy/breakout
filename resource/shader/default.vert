#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uvcoord;

out vec3 vertexColor;
out vec2 uv;

void main() {
    uv = uvcoord;
    vertexColor = color;
    gl_Position = vec4(aPos, 1.0);
}
