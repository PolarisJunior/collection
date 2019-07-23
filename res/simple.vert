#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
// uniform mat4 coordinate_transform;
uniform mat4 model_normal;

out vec2 texCoord;
out vec3 normal;

void main()
{
// "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    gl_Position =  projection * view  * model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
    // normal = (coordinate_transform * vec4(aNormal, 0)).xyz;
    normal = (model_normal * vec4(-aNormal, 0)).xyz;
}