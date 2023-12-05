#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aVel;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float u_time;
out vec4 FragPos;
out vec3 Normal;
void main()
{
FragPos = model * vec4(aPos + aVel * u_time , 1.0f);
    Normal = aVel;
    gl_Position = proj * view * model * vec4(aPos + aVel * u_time , 1.0f);
}