#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 pos;

uniform float horizOffset;

void main() {
   gl_Position = vec4(aPos.x + horizOffset, -aPos.y, aPos.z, 1.0); // put every vertex exactly where it should be with an alpha of 1
   ourColor = aColor;
   pos = aPos;
}
