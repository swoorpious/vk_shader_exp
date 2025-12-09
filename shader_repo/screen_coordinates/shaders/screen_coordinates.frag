#version 450

layout(location = 0) in vec2 inUV;
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UBO {
    vec2 iResolution;
    float iTime;
} ubo;

void main()
{
    outColor = vec4(inUV.x, inUV.y, 0.5 + 0.5 * sin(ubo.iTime), 1.0);
}