#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
flat out int discardDraw;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    if (aPos.x == 2147483647 && aPos.y == 2147483647 && aPos.z == 2147483647)
        discardDraw = 1;
    else
        discardDraw = 0;

    FragPos = aPos;
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    
    gl_Position = proj * view * vec4(FragPos, 1.0);
}