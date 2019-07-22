#version 330 core
out vec4 FragColor;
uniform float u_time;
void main()
{
    FragColor = vec4(sin(u_time*.01), 0.5f, 0.2f, 1.0f);
}      