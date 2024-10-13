#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out float depth;

void main() {
    depth = gl_Position.z / gl_Position.w;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}