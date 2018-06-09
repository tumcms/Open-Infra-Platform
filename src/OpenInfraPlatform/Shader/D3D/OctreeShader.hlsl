
cbuffer WorldBuffer
{
    float4x4 viewProjection;
    float4x4 projection;
    float4x4 view;
    float3 cam;
};

struct ApplicationToVertex
{
    float3 position : Position;
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

VertexToFragment VS_main(ApplicationToVertex app2vs)
{
    VertexToFragment vtf = (VertexToFragment) 0;
    vtf.position = mul(viewProjection, float4(app2vs.position, 1));
    vtf.color = float3(1, 1, 1);
    return vtf;
}

FragmentToPixel PS_main(VertexToFragment vtf)
{
    FragmentToPixel final;
    final.color = float4(vtf.color.xyz, 1.0f);
    return final;
}