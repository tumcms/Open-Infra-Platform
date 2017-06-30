/*
    Copyright (c) 2016-2017 Technical University of Munich
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

SamplerState sampler_ : register(s0);
TextureCube<float4> texDiffuseMap : register(t0);

cbuffer WorldBuffer
{
    float4x4 viewProjection;
    float4x4 projection;
    float4x4 view;
    float3 cam;
};

//----------------------------------------------------------------------------
struct ApplicationToVertex
{
    float3 position : position;
    float3 normal : NORMAL;
    float2 uv : uv;
};

//----------------------------------------------------------------------------
struct VertexToFragment
{
    float4 position : SV_POSITION;
    float3 uvw : uvw;
};

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------
VertexToFragment VS_main(ApplicationToVertex app2vs)
{
    VertexToFragment vtf = (VertexToFragment) 0;

    vtf.uvw = app2vs.position.xyz;
    vtf.position = float4(app2vs.position.xyz, 1);
    vtf.position.xz *= 2.0f;
    vtf.position.xyz += cam;
    vtf.position = mul(viewProjection, vtf.position);
    
    return vtf;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------

float4 PS_main(VertexToFragment vtf, bool frontFace : SV_IsFrontFace): SV_Target
{
    return float4(texDiffuseMap.Sample(sampler_, vtf.uvw).xyz, 1.0f);
}