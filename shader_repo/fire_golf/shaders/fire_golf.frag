// shader by @xordev on twitter
// source: https://x.com/XorDev/status/2041967895094149509
#version 450

layout(location = 0) in vec2 inUV;
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform UBO {
    vec2 iResolution;
    float iTime;
} ubo;

void main()
{
    float z = 0.0;
    float d = 0.0;
    vec4 color = vec4(0.0);
    float t = ubo.iTime * 0.5;

    vec3 r = vec3(ubo.iResolution.x, ubo.iResolution.y, ubo.iResolution.y);

    // gl_FragCoord.xyz -> Z is 0.0 since we draw a 2D triangle
    // transform: flip the y-axis to correct vulkan's top-left origin vs opengl's bottom-left
    vec3 fc = vec3(gl_FragCoord.x, ubo.iResolution.y - gl_FragCoord.y, 0.0);

    vec3 rd = normalize(2.0 * fc - r);

    // raymarching loop with 70 steps
    for (int i = 0; i < 70; i++)
    {
        vec3 p = z * rd;
        p.z += 5.0 + cos(t);

        // rotate matrix
        vec4 c = cos(t + p.y / 4.0 + vec4(0.0, 8.0, 5.0, 0.0));
        p.xz *= mat2(c.xy, c.zw);

        d = 2.0;

        for (int j = 0; j < 6; j++)
        {
            d /= 0.8;
            vec3 k = p.yzx - vec3(t, 0.0, 0.0) * 8.0;
            p += cos((k) * d + t) / d;
        }

        d = 0.01 + abs(length(p.xz) + p.y * 0.3 - 1.0) / 9.0;
        z += d;

        // color accumulation
        color += (sin(p.y / 2.0 - vec4(0.0, 1.0, 2.0, 0.0)) + 1.1) / d;
    }

    // tone mapping
    color = tanh(color / 1000.0);
    outColor = vec4(color.rgb, 1.0);
}