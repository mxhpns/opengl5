#version 330

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 color;

smooth out vec4 _color;

void main() {
    gl_Position = pos;
    _color = color;
}
