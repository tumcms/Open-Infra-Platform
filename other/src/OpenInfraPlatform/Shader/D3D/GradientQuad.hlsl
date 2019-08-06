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

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

//SamplerState		samplerLinear;
//Texture2D<float4>	tex0;

cbuffer ShaderVariables
{
    float time : packoffset(c0);
    float2 resolution : packoffset(c1);
    float2 mouse : packoffset(c2);
    int snow : packoffset(c3);
};

////////////////////////////////////////////////////////////////////////////
struct VertexToFragment
{
	float4 position				: SV_POSITION;
	float2 uv					: uv;
};

////////////////////////////////////////////////////////////////////////////
VertexToFragment VS_main (uint id : SV_VertexID)
{
	VertexToFragment vtf = (VertexToFragment)0;

    switch (id) 
	{
		case 0:
			vtf.position =  float4 (-1, 1, 0, 1);
			vtf.uv = float2(0, 1);
			break;
		case 1:
			vtf.position =  float4 (-1, -1, 0, 1);
			vtf.uv = float2(0, 0);
			break;
		case 2: 
			vtf.position = float4 (1, 1, 0, 1);
			vtf.uv = float2(1, 1);
			break;
		case 3: 
			vtf.position = float4 (1, -1, 0, 1);
			vtf.uv = float2(1, 0);
			break;
		default: 
			vtf.position = float4 (0, 0, 0, 0);
			vtf.uv = float2(0, 0);
			break;
    }

	return vtf;
}

//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------

float4 PS_main (VertexToFragment vtf) : SV_Target0
{
	float4 top		= float4(  40.0/255.0,  40.0/255.0,  40.0/255.0, 1.0 );
	float4 bottom	= float4( 153.0/255.0, 160.0/255.0, 163.0/255.0, 1.0 );

    float4 color = lerp(top, bottom, vtf.uv.y);


	// Copied and modified code from https://www.shadertoy.com/view/ldsGDn
	// Original copyright notice:

	// Copyright (c) 2013 Andrew Baldwin (twitter: baldand, www: http://thndl.com)
	// License = Attribution-NonCommercial-ShareAlike (http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US)

	// "Just snow"
	// Simple (but not cheap) snow made from multiple parallax layers with randomly positioned 
	// flakes and directions. Also includes a DoF effect. Pan around with mouse.

    if (snow)
    {
        float2 iMouse = mouse;
        float2 iResolution = resolution;
        float iGlobalTime = time;

        int LAYERS = 50;
        float DEPTH = 0.5;
        float WIDTH = 0.3;
        float SPEED = 0.6;

        const float3x3 p = float3x3(13.323122, 23.5112, 21.71123, 21.1212, 28.7312, 11.9312, 21.8112, 14.7212, 61.3934);
        float2 uv = iMouse.xy / iResolution.xy + float2(1., iResolution.y / iResolution.x) * vtf.uv / iResolution.xy;
        float3 acc = float3(0.0, 0.0, 0.0);
        float dof = 5. * sin(iGlobalTime * .1);
        for (int i = 0; i < LAYERS; i++)
        {
            float fi = float(i);
            float2 q = uv * (1. + fi * DEPTH);
            q += float2(q.y * (WIDTH * fmod(fi * 7.238917, 1.) - WIDTH * .5), SPEED * iGlobalTime / (1. + fi * DEPTH * .03));
            float3 n = float3(floor(q), 31.189 + fi);
            float3 m = floor(n) * .00001 + frac(n);
            float3 mp = (31415.9 + m) / frac(mul(p, m));
            float3 r = frac(mp);
            float2 s = abs(fmod(q, 1.) - .5 + .9 * r.xy - .45);
            s += .01 * abs(2. * frac(10. * q.yx) - 1.);
            float d = .6 * max(s.x - s.y, s.x + s.y) + max(s.x, s.y) - .01;
            float edge = .005 + .05 * min(.5 * abs(fi - 5. - dof), 1.);
            acc += float3(smoothstep(edge, -edge, d) * (r.x / (1. + .02 * fi * DEPTH)), smoothstep(edge, -edge, d) * (r.x / (1. + .02 * fi * DEPTH)), smoothstep(edge, -edge, d) * (r.x / (1. + .02 * fi * DEPTH)));
        }
        color += float4(float3(acc), 1.0);
    }
    return color;
}