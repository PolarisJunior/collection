#version 330 core
in vec2 texCoord;
in vec3 normal;

in vec3 lightDir;

out vec4 FragColor;

uniform float u_time;
uniform sampler2D u_texture;
void main()
{
    float kAmbient = .4;
    float kDiffuse = .6;

    float NL = max(0, -dot(normal, lightDir));

    vec2 center = vec2(0.5f, 0.5f);
    float dist = distance(texCoord, center);
    // FragColor = vec4(texCoord.x, texCoord.x, texCoord.x, 1.0f);
    vec3 c = texture(u_texture, texCoord).xyz;
    FragColor = vec4(c.xyz * kAmbient + c.xyz * NL * kDiffuse, 1.0f);
    //FragColor = vec4((normal), 1.0f);

}