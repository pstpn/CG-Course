#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aVel;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform float u_time;

out vec4 FragPos;
out vec3 Normal;
out vec4 figureColor;

vec3 minRoomVert = vec3(1.000000, 1.000000, 1.000000);
vec3 maxRoomVert = vec3(-1.000000, -1.000000, -1.000000);


bool isInsideRoom(vec3 point)
{
    return all(greaterThanEqual(point, minRoomVert)) && all(lessThanEqual(point, maxRoomVert));
}

vec3 getNormal(vec3 point)
{
    int x = int(point.x), y = int(point.y), z = int(point.z);

    if (x == 1)
        return vec3(1, 0, 0);
    else if (x == -1)
        return vec3(-1, 0, 0);
    else if (y == 1)
        return vec3(0, 1, 0);
    else if (y == -1)
        return vec3(0, -1, 0);
    else if (z == -1)
        return vec3(0, 0, -1);

    return vec3(0, 0, 0);
}

void main()
{
    FragPos = model * vec4(aPos + aVel * u_time , 0.5);
    Normal = aVel;
    if (!isInsideRoom(FragPos.xyz))
    {
        vec3 normal = getNormal(FragPos.xyz);
        aVel = aVel - 2.0 * dot(aVel, normal) * normal;
    }
    else
        figureColor = FragPos;

    gl_Position = proj * view * model * vec4(aPos + aVel * u_time , 1.0);
}