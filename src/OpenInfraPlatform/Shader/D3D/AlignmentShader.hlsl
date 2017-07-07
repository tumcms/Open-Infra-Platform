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

//#include "brdf_h.hlsl"
#include "brdf.hlsl.inc"

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

cbuffer SettingsBuffer : register(b0)
{
    int bDrawColored : packoffset(c0);
    int bHighlightSelected : packoffset(c1);
    int bDrawFlattened : packoffset(c2);
    int bDrawTextured : packoffset(c3);
    int selectedAlignmentIndex : packoffset(c4);
}; 

cbuffer ColorBuffer : register(b1)
{
    float4 alignment : packoffset(c0);
    float4 selected : packoffset(c1);
    float4 highlight : packoffset(c2);
    float4 crossSection : packoffset(c3);
    float4 designCrossSection : packoffset(c4);
    float4 clothoid : packoffset(c5);
    float4 arc : packoffset(c6);
    float4 straight : packoffset(c7);
    float4 bloss : packoffset(c8);
    float4 roadBody : packoffset(c9);
    float4 roadBodyConvex : packoffset(c10);
    float4 roadBodyConcave : packoffset(c11);
};

cbuffer PickIdBuffer: register(b2)
{
    uint current : packoffset(c0);
};

struct ApplicationToVertex
{
	float3 position : position;
    uint3 id : Id;
};

struct ApplicationToVertexSolid
{
    float3 position : position;
    float3 normal : Normal;
    uint3 id : Id;
    float2 uv : Uv;
};

struct VertexToGeometry
{
	float4 position : position;
    float4 color : COLOR;
	float size : SIZE;
    uint pickId : Id;
};

struct GeometryToPixel
{
	float4 position : SV_POSITION;
    float4 color : COLOR;
    uint pickId : Id;
};

struct VertexToPixel
{
    float4 position : SV_POSITION;
    float4 worldPosition : worldposition;
    float4 color : COLOR;
    float3 normal : norm;
    uint2 id : Id;
    float2 uv : TEXCOORD;
};

struct FragmentToPickBuffer
{
    uint pick : SV_Target0;
};


float4 getColor(int id)
{
	switch (id)
	{
	case 0:	return bDrawColored ? straight : alignment;
	case 1: return bDrawColored ? arc : alignment;
    case 2: return bDrawColored ? clothoid : alignment;
    case 3: return bDrawColored ? bloss : alignment;
	case 4: return crossSection;
	case 5:	return designCrossSection;
	case 6:
	case 7: return roadBody;
    case 8: return roadBodyConcave;
    case 9: return roadBodyConvex;
	default: return float4(1, 0, 0, 1);
	}
}

VertexToGeometry VS_line(ApplicationToVertex app2vs)
{
	VertexToGeometry vs2gs = (VertexToGeometry)0;

    if (bDrawFlattened)
        app2vs.position.z = 0;

	vs2gs.position = mul(viewProjection, float4(app2vs.position.xzy, 1));
    vs2gs.color = getColor(app2vs.id[1]);
    vs2gs.pickId = app2vs.id[2];
	vs2gs.size = 2;
    
    if(bHighlightSelected && app2vs.id[0] == (uint)selectedAlignmentIndex)
        vs2gs.color = selected;
    
    if(current == vs2gs.pickId)
        vs2gs.color = highlight;
    
	return vs2gs;
}

VertexToGeometry VS_line_pick(ApplicationToVertex app2vs)
{
	VertexToGeometry vs2gs = (VertexToGeometry)0;

	if (bDrawFlattened)
		app2vs.position.z = 0;

	vs2gs.position = mul(viewProjection, float4(app2vs.position.xzy, 1));
	vs2gs.color = alignment;
	vs2gs.pickId = app2vs.id[2];
	vs2gs.size = 15;

	return vs2gs;
}

VertexToPixel VS_solid(ApplicationToVertexSolid app2vs)
{
    VertexToPixel vs2ps = (VertexToPixel) 0;

    if (bDrawFlattened)
        app2vs.position.z = 0;

    vs2ps.worldPosition = float4(app2vs.position.xyz, 1);
    vs2ps.normal = app2vs.normal;
    vs2ps.position = mul(viewProjection, float4(app2vs.position.xzy, 1));
    vs2ps.color = getColor(app2vs.id[1]);
    if (bHighlightSelected && app2vs.id[0] == (uint) selectedAlignmentIndex)
        vs2ps.color = selected;
    
    if (current == app2vs.id[2])
        vs2ps.color = highlight;

    vs2ps.id = uint2(app2vs.id[1], app2vs.id[2]);
    vs2ps.uv = app2vs.uv;
        
    return vs2ps;
}

void generateLine(in float4 p[4], in float s[2], out float4 v[4])
{
	p[0].xyz /= p[0].w;
	p[1].xyz /= p[1].w;
	p[2].xyz /= p[2].w;
	p[3].xyz /= p[3].w;

	float2 line01 = p[1].xy - p[0].xy;
	float2 line12 = p[2].xy - p[1].xy;
	float2 line23 = p[3].xy - p[2].xy;

	float width = 1.0 / viewport.y * 2;
	float2 ratio = float2(viewport.x, viewport.y);

	float2 normal01 = normalize(float2(-line01.y, line01.x));
	float2 normal12 = normalize(float2(-line12.y, line12.x));
	float2 normal23 = normalize(float2(-line23.y, line23.x));

	float2 tangent1 = normalize(normalize(line12) + normalize(line01));
	float2 miter1 = float2(-tangent1.y, tangent1.x);

	float2 tangent2 = normalize(normalize(line23) + normalize(line12));
	float2 miter2 = float2(-tangent2.y, tangent2.x);

	float d1 = dot(miter1, normal12);
	float d2 = dot(miter2, normal12);

	float2 offset1, offset2;

	if (length(line01) > 0.001 && d1 > cos(60 * 3.14f / 180))
		offset1 = miter1 * s[0] / d1;
	else
		offset1 = normal12 * s[0];

	if (length(line23) > 0.001 && d2 > cos(60 * 3.14f / 180))
		offset2 = miter2 * s[1] / d2;
	else
		offset2 = normal12 * s[1];

	offset1 /= ratio;
	offset2 /= ratio;

	v[0] = float4(p[1].xy + offset1, p[1].z, 1) * p[1].w;
	v[1] = float4(p[1].xy - offset1, p[1].z, 1) * p[1].w;

	v[2] = float4(p[2].xy + offset2, p[2].z, 1) * p[2].w;
	v[3] = float4(p[2].xy - offset2, p[2].z, 1) * p[2].w;
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
void GS_lineStrip(lineadj VertexToGeometry vs2gs[4], inout TriangleStream<GeometryToPixel> outputStream)
{
	float4 p[4] = { vs2gs[0].position, vs2gs[1].position, vs2gs[2].position, vs2gs[3].position };
	float s[2] = { vs2gs[1].size, vs2gs[2].size };

	float4 v[4];
	generateLine(p, s, v);

	float4 color1 = vs2gs[1].color;
	float4 color2 = vs2gs[2].color;

	uint id = vs2gs[1].pickId;

	GeometryToPixel g2p;
	g2p.pickId = id;

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
[maxvertexcount(16)]
void GS_lineList(line VertexToGeometry vs2gs[2], inout TriangleStream<GeometryToPixel> outputStream)
{
	float4 p[2] = { vs2gs[0].position, vs2gs[1].position};
	float s[2] = { vs2gs[0].size, vs2gs[1].size };

	float4 v[4];
	generateLine(p, s, v);

	float4 color1 = vs2gs[0].color;
	float4 color2 = vs2gs[1].color;

	uint id = vs2gs[0].pickId;

	GeometryToPixel g2p;
	g2p.pickId = id;

	g2p.color = color1;
	g2p.position = v[0];
    g2p.pickId = id;
	outputStream.Append(g2p);

	g2p.position = v[1];
    g2p.pickId = id;
	outputStream.Append(g2p);

	g2p.color = color2;
	g2p.position = v[2];
    g2p.pickId = id;
	outputStream.Append(g2p);

	g2p.position = v[3];
    g2p.pickId = id;
	outputStream.Append(g2p);

	outputStream.RestartStrip();
}

Texture2D<float4> texRoadBodySolid : register(t0);
Texture2D<float4> texRoadBodyNormalSolid : register(t1);
sampler samplerLinear : register(s0);


float4 PS_line(GeometryToPixel gs2ps, bool frontFace : SV_IsFrontFace) : SV_Target0
{
	return float4(gs2ps.color.rgb, 1);
}

float4 PS_solid(VertexToPixel vs2ps, bool frontFace : SV_IsFrontFace) : SV_Target0
{
    float4 result;
    float3 N;
    float3 P = vs2ps.worldPosition.xyz;
    if (bDrawTextured && vs2ps.id[0] == 7)
    {
        result = texRoadBodySolid.Sample(samplerLinear, vs2ps.uv);
        N = texRoadBodyNormalSolid.Sample(samplerLinear, vs2ps.uv).xyz;
    }
    else
    {
        result = float4(vs2ps.color.rgb, 1);
        N = vs2ps.normal.xzy;
    }


    N = normalize(N) * frontFace ? 1 : -1;
    
    //camLight = true;
    return float4(brdf(cam, P, N, result.xyz, 0.0, 0.4, 2.4), 1);

}

FragmentToPickBuffer PS_line_pick(GeometryToPixel gs2ps)
{
    FragmentToPickBuffer final = (FragmentToPickBuffer) 0;
    final.pick = gs2ps.pickId;
    return final;
}

FragmentToPickBuffer PS_solid_pick(VertexToPixel vs2ps)
{
    FragmentToPickBuffer final = (FragmentToPickBuffer) 0;
    final.pick = (uint)vs2ps.id[1];
    return final;
}

void VS_main()
{}

void PS_main()
{}