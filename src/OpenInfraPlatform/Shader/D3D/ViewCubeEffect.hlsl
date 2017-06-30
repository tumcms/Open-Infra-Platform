cbuffer CameraTransformations
{
    float4x4 rotation;
    float4x4 projection;
};

cbuffer RenderingDescription
{
    uniform float3 bindingColor : packoffset(c0);
    uniform float3 highlightColor : packoffset(c1);
    uniform float3 faceColor : packoffset(c2);
    uniform float3 textColor : packoffset(c3);
    uniform float textureRange : packoffset(c4);
    uniform float size : packoffset(c5);
    uniform int selectedId : packoffset(c6);
};

cbuffer PickId {
    uint current: packoffset(c0);
};

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
struct ApplicationToVertex
{
    float3 position				: position;
    float2 uv					: uv;
    uint pickid                 : pickid;
    int faceid                  : faceid;
    int regionid                : regionid;
};

//----------------------------------------------------------------------------
struct VertexToFragment
{
    float4 position				: SV_POSITION;
    float3 worldposition		: worldposition;
    float3 normal               : norm;
    float2 texCoord             : tex;
    uint pickid                 : pickid;
    int faceid                  : faceid;
    int regionid                : regionid;
};

//VertexToFragment VS_main(ApplicationToVertex app2vs)
//{
//    VertexToFragment result = (VertexToFragment)0;
//    result.position = mul(worldViewProjection, float4(app2vs.position, 1));
//    result.worldposition = mul(world, float4(app2vs.position, 1)).xyz;
//    result.texCoord = app2vs.uv;
//    result.texCoord.x = 1 - result.texCoord.x;
//    return result;
//}
//----------------------------------------------------------------------------
VertexToFragment VS_main(ApplicationToVertex app2vs)
{
    VertexToFragment result = (VertexToFragment)0;     
    result.position = mul(float4(mul(size, app2vs.position), 1), rotation);
    result.position.z += 2.5f;
    result.position = mul(projection, result.position);
    result.texCoord = app2vs.uv;
    result.pickid = app2vs.pickid;
    result.faceid = app2vs.faceid;
    result.regionid = app2vs.regionid;
    return result;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------
struct FragmentToPixel
{
    float4 color : SV_Target0;
};

struct FragmentToPickBuffer
{
    uint pick : SV_Target0;
};

Texture2D<float4> diffuse: register (t0);
Texture2D<float4> front: register (t1);
Texture2D<float4> back: register (t2);
Texture2D<float4> left: register (t3);
Texture2D<float4> right: register (t4);
Texture2D<float4> top: register (t5);
Texture2D<float4> bottom: register (t6);
sampler samplerLinear : register (s0);

float3 lighting(float3 position, float3 normal, float3 color)
{
    float dist = length(position);
    float l = saturate(1 - dist / 100.f);
    l *= dot(normalize(normal), normalize(-position));

    return lerp(color, color * l, 0.8);
}

FragmentToPixel PS_cube(VertexToFragment v2f)
{
    FragmentToPixel final;
    float4 texColor = float4(0, 0, 0, 0);
    if (v2f.regionid == 2) {
        float2 uv = (v2f.texCoord - float2(textureRange, textureRange)) / (1.0f - (2.0f*textureRange));
        switch (v2f.faceid) {
        case 0: texColor = float4(front.Sample(samplerLinear, uv)); break;
        case 1: texColor = float4(back.Sample(samplerLinear, uv)); break;
        case 2: texColor = float4(left.Sample(samplerLinear, uv)); break;
        case 3: texColor = float4(right.Sample(samplerLinear, uv)); break;
        case 4:	texColor = float4(top.Sample(samplerLinear, uv)); break;
        case 5: texColor = float4(bottom.Sample(samplerLinear, uv)); break;
        default: break;
        }
    }

    float4 color = float4(0, 0, 0, 0);
    if (v2f.regionid == 0) {
        color = float4(bindingColor, 1.0f);
    }
    else {
        color = float4(faceColor, 1.0f);
    }
    
    final.color = texColor.a * texColor + (1.0f - texColor.a) * color;
    
    if (v2f.pickid == current)
    {
        final.color = 0.3f * final.color +  0.7f * float4(highlightColor.xyz, 1.0f);
    }
    return final;
}

FragmentToPickBuffer PS_pick(VertexToFragment v2f)
{
    FragmentToPickBuffer final = (FragmentToPickBuffer)0;
    final.pick = v2f.pickid;
    return final;
}

FragmentToPixel PS_main(VertexToFragment v2f)
{
    FragmentToPixel final;
    final.color = diffuse.Sample(samplerLinear, v2f.texCoord);

    return final;
}
