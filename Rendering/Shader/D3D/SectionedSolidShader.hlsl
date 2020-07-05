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

cbuffer ColorBuffer : register(b0)
{
	float4 diffuseColor : packoffset(c0);
};



struct ApplicationToVertex
{
	float3 position : position;
};

struct ApplicationToVertexSolid
{
	float3 position : position;
	float3 normal : Normal;
};

struct VertexToGeometry
{
	float4 position : position;
	float4 color : COLOR;
};

struct GeometryToPixel
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

struct VertexToPixel
{
	float4 position : SV_POSITION;
	float4 worldPosition : worldposition;
	float4 color : COLOR;
	float3 normal : norm;
};



void generateLine(in float4 p[4], out float4 v[4])
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
		offset1 = miter1 * 2.0 / d1;
	else
		offset1 = normal12 * 2.0;

	if (length(line23) > 0.001 && d2 > cos(60 * 3.14f / 180))
		offset2 = miter2 * 2.0 / d2;
	else
		offset2 = normal12 * 2.0;

	offset1 /= ratio;
	offset2 /= ratio;

	v[0] = float4(p[1].xy + offset1, p[1].z, 1) * p[1].w;
	v[1] = float4(p[1].xy - offset1, p[1].z, 1) * p[1].w;

	v[2] = float4(p[2].xy + offset2, p[2].z, 1) * p[2].w;
	v[3] = float4(p[2].xy - offset2, p[2].z, 1) * p[2].w;
}



VertexToGeometry VS_line(ApplicationToVertex app2vs)
{
	VertexToGeometry vs2gs = (VertexToGeometry)0;

	vs2gs.position = mul(viewProjection, float4(app2vs.position.xzy, 1));
	vs2gs.color = diffuseColor;

	return vs2gs;
}

[maxvertexcount(16)]
void GS_line(lineadj VertexToGeometry vs2gs[4], inout TriangleStream<GeometryToPixel> outputStream)
{
	float4 p[4] = { vs2gs[0].position, vs2gs[1].position, vs2gs[2].position, vs2gs[3].position };
	float4 v[4];
	generateLine(p, v);

	GeometryToPixel g2p;
	g2p.color = vs2gs[1].color;
	g2p.position = v[0];
	outputStream.Append(g2p);

	g2p.position = v[1];
	outputStream.Append(g2p);

	g2p.color = vs2gs[2].color;
	g2p.position = v[2];
	outputStream.Append(g2p);

	g2p.position = v[3];
	outputStream.Append(g2p);

	outputStream.RestartStrip();
}

float4 PS_line(GeometryToPixel gs2ps, bool frontFace : SV_IsFrontFace) : SV_Target0
{
	return float4(gs2ps.color.rgb, 1);
}



VertexToPixel VS_solid(ApplicationToVertexSolid app2vs)
{
	VertexToPixel vs2ps = (VertexToPixel)0;

	vs2ps.worldPosition = float4(app2vs.position.xyz, 1);
	vs2ps.normal = app2vs.normal;
	vs2ps.position = mul(viewProjection, float4(app2vs.position.xzy, 1));
	vs2ps.color = diffuseColor;

	return vs2ps;
}

float4 PS_solid(VertexToPixel vs2ps, bool frontFace : SV_IsFrontFace) : SV_Target0
{
	//camLight = true;
	float3 P = vs2ps.worldPosition.xyz;
	//float3 N = normalize(vs2ps.normal.xzy) * (frontFace ? 1 : -1);
	float3 N = normalize(vs2ps.normal.xzy);
	return float4(brdf(cam, P, N, vs2ps.color.rgb, 0.0, 0.4, 2.4), 1);
}

void VS_main()
{}

void PS_main()
{}
