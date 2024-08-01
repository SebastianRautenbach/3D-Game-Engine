#version 460 core

out vec4 FragColor;
int code = 2 * 20;

void main() {
    // Encode the object ID as a color
    int r = (code & 0x000000FF);
    int g = (code & 0x0000FF00) >> 8;
    int b = (code & 0x00FF0000) >> 16;
    FragColor = vec4(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0, 1.0);
}
