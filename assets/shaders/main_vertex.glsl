#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 uOffset;

void main()
{
    vec3 finalPos = aPos + uOffset;
    gl_Position = vec4(finalPos.x, finalPos.y, finalPos.z, 1.0);
}
