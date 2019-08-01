#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    gl_Position = projection * mat4(mat3(view)) * vec4(aPos, 1.0);
    gl_Position = gl_Position.xyww;
    // mat4 normalizedPV = mat4(mat3(PV));
    // gl_Position = normalizedPV * vec4(aPos, 1.0);
} 