#version 450

layout(location = 0) in vec2 inUV;
layout(location = 0) out vec4 outColor;

// We keep the UBO layout so the C++ pipeline (DescriptorSets) doesn't crash on mismatch
layout(binding = 0) uniform UBO {
    vec2 iResolution;
    float iTime;
} ubo;

void main()
{
    // Debug: Output UV coordinates as color
    // Top-Left should be Green/Black, Bottom-Right should be Red/Yellow
    // Alpha is forced to 1.0 to ensure visibility
    outColor = vec4(inUV.x, inUV.y, 0.5 + 0.5 * sin(ubo.iTime), 1.0);
}