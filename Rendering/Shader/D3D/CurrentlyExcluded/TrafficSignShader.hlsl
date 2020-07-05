// #include <common.hlsl> // including not yet supported

cbuffer WorldBuffer
{
	float4x4 viewProjection;
	float4x4 projection;
	float4x4 view;
	float3 cam;
};

cbuffer Placement
{
    float4x4 transform;
};

//----------------------------------------------------------------------------
struct ApplicationToVertex 
{
    float3 position : position;
};

struct VertexToGeometry
{
    float4 position : position;
};

struct GeometryToPixel
{
    float4 position : SV_POSITION;
    float3 normal : normal;
    float3 worldPosition : worldposition;
    float3 worldNormal : worldnormal;
};

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

VertexToGeometry VS_main(ApplicationToVertex app2vs)
{
    VertexToGeometry result = (VertexToGeometry) 0;

    float4 pos = mul(transform, float4(app2vs.position.xyz, 1));

	result.position = mul(viewProjection, pos);

	return result;
}

[maxvertexcount(3)]void GS_main(triangle VertexToGeometry vs2gs[3], inout TriangleStream<GeometryToPixel> outputStream)
{
    GeometryToPixel gs2ps = (GeometryToPixel) 0;

    float3 v1 = vs2gs[1].position.xyz - vs2gs[0].position.xyz;
    float3 v2 = vs2gs[2].position.xyz - vs2gs[0].position.xyz;
    float3 wn = normalize(cross(normalize(v1), normalize(v2)));
    float3 n = normalize(mul((float3x3) view, wn));

    gs2ps.normal = n;
    gs2ps.worldNormal = wn;

    gs2ps.position = vs2gs[0].position; //mul(viewProjection, float4(vs2gs[0].position, 1));
    gs2ps.worldPosition = vs2gs[0].position.xzy;

    outputStream.Append(gs2ps);

    gs2ps.position = vs2gs[1].position; //mul(viewProjection, float4(vs2gs[1].position, 1));
    gs2ps.worldPosition = vs2gs[1].position.xzy;
    outputStream.Append(gs2ps);

    gs2ps.position = vs2gs[2].position; //mul(viewProjection, float4(vs2gs[2].position, 1));
    gs2ps.worldPosition = vs2gs[2].position.xzy;
    outputStream.Append(gs2ps);
}


//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------

static const float PI = 3.14159265f;

float GGX(float NdotV, float a)
{
    float k = a / 2;
    return NdotV / (NdotV * (1.0f - k) + k);
}

float G_Smith(float a, float nDotV, float nDotL)
{
    return GGX(nDotL, a * a) * GGX(nDotV, a * a);
}

float3 specularBRDF(float3 N, float3 V, float3 L, float3 color, float metallic, float ior, float roughness)
{
    float3 F0 = abs((1.0 - ior) / (1.0 + ior));
    F0 = F0 * F0;
    F0 = lerp(F0, color, metallic);

    float3 H = normalize(L + V);

    float NoV = max(saturate(dot(N, V)), 0.01f);
    float NoH = saturate(dot(N, H));
    float NoL = saturate(dot(N, L));
    float HoV = saturate(dot(H, V));

    if (NoL > 0)
    {
        float a = roughness;
        float a2 = a * a;

        float D = a2 / (PI * pow(pow(NoH, 2) * (a2 - 1) + 1, 2));
        float G = G_Smith(a, NoV, NoL);

        float3 F = F0 + (1 - F0) * pow(1 - HoV, 5);

        return G * D * F;
    }

    return 0;
}

float3 diffuseBRDF(float3 N, float3 V, float3 L, float3 color, float metallic, float ior)
{
    float3 F0 = abs((1.0 - ior) / (1.0 + ior));
    F0 = F0 * F0;
    F0 = lerp(F0, color, metallic);

    float3 H = normalize(L + V);

    float NoL = saturate(dot(N, L));
    float NoH = saturate(dot(N, H));
    float HoV = saturate(dot(H, V));

    if (NoL > 0)
    {
        float3 F = F0 + (1 - F0) * pow(1 - HoV, 5);
        return color * NoL * (1 - F);
    }

    return 0;
}

static float3 lightColor = 0.7f;
static float3 lightDirection = float3(2, 4, 3);
static float3 ambientColor = float3(1.0f, 0.4f, 0.4f);
static bool camLight = true;

float3 brdf(float3 P, float3 N, float3 color, float metallic, float roughness, float ior)
{
    float3 result = 0;

    float3 V = normalize(cam - P);

    float3 L = normalize(lightDirection);
    if (camLight)
        L = V;

    float3 direct = 0;
    direct += specularBRDF(N, V, L, color, metallic, ior, roughness);
    direct += diffuseBRDF(N, V, L, color, metallic, ior);
    direct *= lightColor;

    float3 ambient = 0;
    ambient += diffuseBRDF(N, V, N, color, metallic, ior);
    ambient *= ambientColor;

    result = direct + ambient;

    return result;
}

float4 PS_main(GeometryToPixel gs2ps, bool frontFace : SV_IsFrontFace) : SV_Target
{
    float3 finalColor = 0.5f; // float3(0,0,0.5f);
    float2 uv = gs2ps.worldPosition.xy / 300;

    float3 N = normalize(gs2ps.worldNormal * (frontFace ? 1 : -1));
    float3 P = gs2ps.worldPosition.xzy;

    
    finalColor = brdf(P, N, finalColor, 0, 0.4, 2.4);

    return float4(finalColor, 1);
}