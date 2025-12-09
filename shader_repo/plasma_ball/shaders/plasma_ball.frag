#version 450

layout(location = 0) in vec2 inUV;
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UBO {
    vec2 iResolution;
    float iTime;
} ubo;

void main()
{
    vec2 r = ubo.iResolution;
    float t = ubo.iTime;
    vec4 FC = gl_FragCoord;

    float scaleFactor = 0.7;

    vec4 o = vec4(1e-5);
    vec2 l = vec2(0.0);
    vec2 i = vec2(0.0);

    vec2 p = ((FC.xy * 2.0 - r) / r.y) / scaleFactor;

    float dotP = dot(p, p);
    l += 4.0 - 4.0 * abs(0.7 - dotP);
    vec2 v = p * l;

    for (int k = 0; k < 8; k++) {
        i.y += 1.0;
        v += cos(v.yx * i.y + i + t) / i.y + 0.7;
        o += (sin(v.xyyx) + 1.0) * abs(v.x - v.y);
    }

    // final color mapping
    vec4 exponent = l.x - 4.0 - p.y * vec4(-1.0, 1.0, 2.0, 0.0);
    o = tanh(5.0 * exp(exponent) / o);

    // fix for brightness issues at render
    vec3 finalColor = o.rgb * 1.5;
    outColor = vec4(finalColor, 1.0);
}