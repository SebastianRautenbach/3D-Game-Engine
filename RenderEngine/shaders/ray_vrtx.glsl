#version 460 core

layout(location = 0) in vec3 aPos;

mat4 model = mat4(1);
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
