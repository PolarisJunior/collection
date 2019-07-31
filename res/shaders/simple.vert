#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 model_normal;
uniform mat4 PV;

out vec2 texCoord;
out vec3 normal;

void main()
{
    gl_Position = PV * model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    normal = (model_normal * vec4(aNormal, 0)).xyz;
}