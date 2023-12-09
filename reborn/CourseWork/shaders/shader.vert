#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

//out vec4 FragPos;
//out vec3 Normal;
//out vec4 figureColor;

void main()
{
    //FragPos = model * vec4(aPos + aVel * u_time , 0.5);
    //Normal = aVel;
    gl_Position = proj * view * model * vec4(aPos, 1);
}