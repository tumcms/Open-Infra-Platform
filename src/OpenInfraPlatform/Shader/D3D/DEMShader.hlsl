/*
	Copyright (c) 2017 Technical University of Munich
	Chair of Computational Modeling and Simulation.

	TUM Open Infra Platform is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License Version 3
	as published by the Free Software Foundation.

	TUM Open Infra Platform is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "brdf.hlsl.inc"

cbuffer WorldBuffer {
	float4x4 viewProjection;
	float4x4 projection;
	float4x4 view;
	float3 cam;
};

cbuffer SettingsBuffer {
	int bTerrainTextured;
	int bTerrainUseColorRamp;
	int bTerrainDisplayIsoLines;
	int bSnow;
	float minHeight;
	float maxHeight;
	int padding1;
	int padding2;
};

struct ApplicationToVertex {
	float3 position : position;
};

struct VertexToGeometry {
	float3 position : position;
	float height : height;
};

struct GeometryToPixel {
	float4 position : SV_POSITION;
	float3 normal : normal;
	float3 worldPosition : worldposition;
	float3 worldNormal : worldnormal;
	float height : height;
};

VertexToGeometry VS_main(ApplicationToVertex app2vs) {
	VertexToGeometry vs2gs = (VertexToGeometry)0;
	vs2gs.position = app2vs.position.xzy; // swizzle!
	vs2gs.height = app2vs.position.z;
	return vs2gs;
}

[maxvertexcount(3)] void GS_main(triangle VertexToGeometry vs2gs[3], inout TriangleStream<GeometryToPixel> outputStream) {
	GeometryToPixel gs2ps = (GeometryToPixel)0;

	float3 v1 = vs2gs[2].position - vs2gs[0].position;
	float3 v2 = vs2gs[1].position - vs2gs[0].position;
	float3 wn = normalize(cross(normalize(v1), normalize(v2)));
	float3 n = normalize(mul((float3x3)view, wn));

	gs2ps.normal = n;
	gs2ps.worldNormal = wn;

	gs2ps.position = mul(viewProjection, float4(vs2gs[0].position, 1));
	gs2ps.worldPosition = vs2gs[0].position.xzy;
	gs2ps.height = vs2gs[0].height;
	outputStream.Append(gs2ps);

	gs2ps.position = mul(viewProjection, float4(vs2gs[1].position, 1));
	gs2ps.worldPosition = vs2gs[1].position.xzy;
	gs2ps.height = vs2gs[1].height;
	outputStream.Append(gs2ps);

	gs2ps.position = mul(viewProjection, float4(vs2gs[2].position, 1));
	gs2ps.worldPosition = vs2gs[2].position.xzy;
	gs2ps.height = vs2gs[2].height;
	outputStream.Append(gs2ps);
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------

Texture2D<float4> texDiffuseMap : register(t0);
Texture1D<float4> texGradientRamp : register(t1);
sampler sampler_ : register(s0);
sampler colorRampSampler_ : register(s1);

//static const float PI = 3.14159265f;

/*
float GGX(float NdotV, float a) {
	float k = a / 2;
	return NdotV / (NdotV * (1.0f - k) + k);
}

float G_Smith(float a, float nDotV, float nDotL) {
	return GGX(nDotL, a * a) * GGX(nDotV, a * a);
}

float3 specularBRDF(float3 N, float3 V, float3 L, float3 color, float metallic, float ior, float roughness) {
	float3 F0 = abs((1.0 - ior) / (1.0 + ior));
	F0 = F0 * F0;
	F0 = lerp(F0, color, metallic);

	float3 H = normalize(L + V);

	float NoV = max(saturate(dot(N, V)), 0.01f);
	float NoH = saturate(dot(N, H));
	float NoL = saturate(dot(N, L));
	float HoV = saturate(dot(H, V));

	if (NoL > 0) {
		float a = roughness;
		float a2 = a * a;

		float D = a2 / (PI * pow(pow(NoH, 2) * (a2 - 1) + 1, 2));
		float G = G_Smith(a, NoV, NoL);

		float3 F = F0 + (1 - F0) * pow(1 - HoV, 5);

		return G * D * F;
	}

	return 0;
}

float3 diffuseBRDF(float3 N, float3 V, float3 L, float3 color, float metallic, float ior) {
	float3 F0 = abs((1.0 - ior) / (1.0 + ior));
	F0 = F0 * F0;
	F0 = lerp(F0, color, metallic);

	float3 H = normalize(L + V);

	float NoL = saturate(dot(N, L));
	float NoH = saturate(dot(N, H));
	float HoV = saturate(dot(H, V));

	if (NoL > 0) {
		float3 F = F0 + (1 - F0) * pow(1 - HoV, 5);
		return color * NoL * (1 - F);
	}

	return 0;
}

static float3 lightColor = 0.7f;
static float3 lightDirection = float3(2, 4, 3);
static float3 ambientColor = 0.4f;
static bool camLight = false;

float3 brdf(float3 P, float3 N, float3 color, float metallic, float roughness, float ior) {
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
*/

float3 snow(float3 baseColor, float3 P, float3 N, float2 uv) {
	float3 S = float3(0, 1, 0);
	float l = dot(N, S);
	l = smoothstep(0.9, 1, l) - 0.1;

	float3 snow = 0.8f;

	N.xy += (texDiffuseMap.Sample(sampler_, uv).rg * 2 - 1) * 0.2;

	N = normalize(N);

	camLight = false;
	snow = brdf(cam, P, N, 1, 0, 0.8, 1.4);

	return lerp(baseColor, snow, l);
}
float4 PS_main(GeometryToPixel gs2ps, bool frontFace : SV_IsFrontFace) : SV_Target {
	float3 finalColor = 0.5f; // float3(0,0,0.5f);
	float2 uv = gs2ps.worldPosition.xy / 300;

	if (bTerrainTextured) {
		finalColor = texDiffuseMap.Sample(sampler_, uv).rgb;
	}

	if (bTerrainUseColorRamp) {
		float range = maxHeight - minHeight;
		float t = (gs2ps.height + 0.5 * range) / range;

		if (bTerrainTextured)
			finalColor = 0.5 * finalColor + 0.5 * texGradientRamp.Sample(sampler_, t).rgb;
		else
			finalColor = texGradientRamp.Sample(colorRampSampler_, t).xyz;
	}

	if (bTerrainDisplayIsoLines) {
		float gridSize = 1;  // in worldSpace
		float gridWidth = 1; // in Pixels

		float height = gs2ps.worldPosition.z;

		float f = abs(frac(height / gridSize + 0.5) - 0.5);
		float df = fwidth(height / gridSize);

		finalColor *= smoothstep(-gridWidth * df, gridWidth * df, f);
	}

	float3 N = normalize(gs2ps.worldNormal * (frontFace ? 1 : -1));
	float3 P = gs2ps.worldPosition.xzy;

	camLight = true;
	finalColor = brdf(cam, P, N, finalColor, 0, 0.4, 2.4);

	if (bSnow) {
		finalColor = snow(finalColor, P, N, uv);
	}

	return float4(finalColor, 1);
}

uint PS_pick(GeometryToPixel gs2ps, bool frontFace : SV_IsFrontFace) : SV_Target {
	return 0; // TODO
}