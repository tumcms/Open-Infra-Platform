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

cbuffer WorldBuffer
{
	float4x4 viewProjection;
	float4x4 projection;
	float4x4 view;
};

cbuffer ViewportBuffer
{
	int2 viewport;
};

struct ApplicationToVertex
{
	float3 position : position;
	float4 color : COLOR;
	float size : size;
};

struct VertexToGeometry
{
	float4 position : position;
	float4 color : color;
	float size : size;
};

struct GeometryToPixel
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VertexToGeometry VS_main(ApplicationToVertex app2vs)
{
	VertexToGeometry vs2gs = (VertexToGeometry)0;
	vs2gs.position = mul(viewProjection, float4(app2vs.position.xzy, 1));
	vs2gs.color = app2vs.color;
	vs2gs.size = app2vs.size;
	
	return vs2gs;
}

float2 project(float4 position)
{
	float4 result = mul(projection, position);
	result /= result.w;
	return result.xy * viewport;
}


void generateLine(float4 p0, float4 p1, float3 color0, float3 color1, float size0, float size1, inout TriangleStream<GeometryToPixel> outputStream)
{
	float w0 = p0.w;
	float w1 = p1.w;

	p0.xyz /= w0;
	p1.xyz /= w1;

	float3 line01 = p1.xyz - p0.xyz;
	float3 dir = normalize(line01);

	float3 ratio = float3(viewport.y, viewport.x, 0);
	ratio = normalize(ratio);

	float3 unit_z = normalize(float3(0, 0, -1));
	float3 normal = normalize(cross(unit_z, dir) * ratio);
	float width = 1.0 / viewport.y * 2;


	float3 dir_offset = dir * ratio * width;
	float3 normal_scaled = normal * ratio * width;

	float3 p0_ex = p0.xyz - dir_offset;
	float3 p1_ex = p1.xyz + dir_offset;

	GeometryToPixel v[4];

	v[0].position = float4(p0_ex - normal_scaled * size0, 1) * w0;
	v[0].color = float4(color0, 1);

	v[1].position = float4(p0_ex + normal_scaled * size0, 1) * w0;
	v[1].color = float4(color0, 1);;

	v[2].position = float4(p1_ex + normal_scaled * size1, 1) * w1;
	v[2].color = float4(color1, 1);;

	v[3].position = float4(p1_ex - normal_scaled * size1, 1) * w1;
	v[3].color = float4(color1, 1);;

	outputStream.Append(v[2]);
	outputStream.Append(v[1]);
	outputStream.Append(v[0]);

	outputStream.RestartStrip();

	outputStream.Append(v[3]);
	outputStream.Append(v[2]);
	outputStream.Append(v[0]);

	outputStream.RestartStrip();
}

[maxvertexcount(16)]
void GS_main(line VertexToGeometry vs2gs[2], inout TriangleStream<GeometryToPixel> outputStream)
{
	float4 p0 = vs2gs[0].position;
	float4 p1 = vs2gs[1].position;

	float size0 = vs2gs[0].size;
	float size1 = vs2gs[1].size;

	float3 color0 = vs2gs[0].color.rgb;
	float3 color1 = vs2gs[1].color.rgb;

	generateLine(p0, p1, color0, color1, size0, size1, outputStream);
}

float4 PS_main(GeometryToPixel gs2ps, bool frontFace : SV_IsFrontFace) : SV_Target
{
	return float4(gs2ps.color.rgb, 1);
}