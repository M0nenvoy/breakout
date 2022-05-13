#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 uv;

void main() {
    float alpha = 1;
    FragColor = vec4(vertexColor, alpha);
}
