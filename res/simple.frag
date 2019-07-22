#version 330 core
in vec2 texCoord;
out vec4 FragColor;
uniform float u_time;
void main()
{
    vec2 center = vec2(0.5f, 0.5f);
    float dist = distance(texCoord, center);
    FragColor = vec4(dist, 0, 0, 1.0f);
}      