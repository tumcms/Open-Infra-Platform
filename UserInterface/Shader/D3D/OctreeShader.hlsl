
cbuffer WorldBuffer
{
    float4x4 viewProjection;
    float4x4 projection;
    float4x4 view;
    float3 cam;
};

cbuffer ViewportBuffer
{
    int2 viewport;
};

struct ApplicationToVertex
{
    float3 position : Position;   
};

struct VertexToGeometry
{
    float4 position : position;
    float4 color : COLOR;
    float size : SIZE;
};

struct GeometryToPixel
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    uint pickId : Id;
};


struct VertexToFragment
{
    float4 position : SV_POSITION;
    float3 color : Color;
};

struct FragmentToPixel
{
    float4 color : SV_Target0;
};

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

VertexToGeometry VS_main(ApplicationToVertex app2vs)
{
    VertexToGeometry vtg = (VertexToGeometry) 0;
    vtg.position = mul(viewProjection, float4(app2vs.position.xzy, 1));
    vtg.color = float4(0, 1, 0, 1);
    vtg.size = 2;
    return vtg;
}

void generateLine(in float4 p[2], in float s[2], out float4 v[4])
{
    p[0].xyz /= p[0].w;
    p[1].xyz /= p[1].w;

    float2 line01 = p[1].xy - p[0].xy;

    float width = 1.0 / viewport.y * 2;
    float2 ratio = float2(viewport.x, viewport.y);

    float2 normal01 = normalize(float2(-line01.y, line01.x));

    float2 offset0 = normal01 * s[0];
    float2 offset1 = normal01 * s[1];

    offset0 /= ratio;
    offset1 /= ratio;

    v[0] = float4(p[0].xy + offset0, p[0].z, 1) * p[0].w;
    v[1] = float4(p[0].xy - offset0, p[0].z, 1) * p[0].w;

    v[2] = float4(p[1].xy + offset1, p[1].z, 1) * p[1].w;
    v[3] = float4(p[1].xy - offset1, p[1].z, 1) * p[1].w;
}

[maxvertexcount(16)]
void GS_main(line VertexToGeometry vs2gs[2], inout TriangleStream<GeometryToPixel> outputStream)
{
    float4 p[2] = { vs2gs[0].position, vs2gs[1].position };
    float s[2] = { vs2gs[0].size, vs2gs[1].size };

    float4 v[4];
    generateLine(p, s, v);

    float4 color1 = vs2gs[0].color;
    float4 color2 = vs2gs[1].color;

    GeometryToPixel g2p = (GeometryToPixel)0;

    g2p.color = color1;
    g2p.position = v[0];
    outputStream.Append(g2p);

    g2p.position = v[1];
    outputStream.Append(g2p);

    g2p.color = color2;
    g2p.position = v[2];
    outputStream.Append(g2p);

    g2p.position = v[3];
    outputStream.Append(g2p);

    outputStream.RestartStrip();
}

FragmentToPixel PS_main(GeometryToPixel gtp)
{
    FragmentToPixel final;
    final.color = float4(gtp.color.xyz, 1.0f);
    return final;
}