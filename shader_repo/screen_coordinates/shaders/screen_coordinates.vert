#version 450

layout (location = 0) out vec2 outUV;

void main()
{
    // Generates a fullscreen triangle (indices 0, 1, 2)
    // Map Vertex Index to UV: (0,0), (2,0), (0,2)
    outUV = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);

    // Map UV to Clip Space [-1, 1]
    gl_Position = vec4(outUV * 2.0f - 1.0f, 0.0f, 1.0f);
}