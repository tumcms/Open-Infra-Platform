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


struct ApplicationToVertex {
	float4 position : position;
};

struct VertexToPixel {
	float4 position : SV_POSITION;
	float2 uv : uv;
};

VertexToPixel VS_main(ApplicationToVertex app2vs) {
	VertexToPixel vs2ps = (VertexToPixel)0;
	vs2ps.position = mul(viewProjection, float4(app2vs.position.x, -20, app2vs.position.y, 1));
	vs2ps.uv = app2vs.position.zw;
	return vs2ps;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------

Texture2D<float4> mapTexture : register(t0);
sampler sampler_ : register(s0);


float4 PS_main(VertexToPixel vs2ps, bool frontFace : SV_IsFrontFace) : SV_Target {
	
	float3 finalColor = mapTexture.Sample(sampler_, vs2ps.uv);

	return float4(finalColor, 1);
}