//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------

cbuffer WorldBuffer
{
    float4x4 viewProjection;
    float4x4 projection;
    float4x4 view;
    float3 cam;
};

cbuffer SettingsBuffer
{
    float4 positions[4];
    float pointSize;
    bool bUseUniformPointSize;
    bool bDrawColored;
};

cbuffer ViewportBuffer
{
    int2 viewport;
};

struct ApplicationToVertex
{
	float3 position			: Position;
	float4 color			: Color;
};

struct VertexToGeometry
{
	float3 worldPosition		: position;
	float4 color				: color;
};

struct VertexToFragment
{
    float4 position : SV_POSITION;
    float4 color : Color;
};

struct GeometryToFragmet
{
	float4 position				: SV_POSITION;
	float4 color				: color;
};

struct FragmentToPixel
{
    float4 color : SV_Target0;
};

//----------------------------------------------------------------------------
// Vertex Shader
//----------------------------------------------------------------------------
VertexToGeometry VS_main_old(ApplicationToVertex app2vs)
{
	VertexToGeometry vtf = (VertexToGeometry)0;

    vtf.worldPosition = app2vs.position.xyz;
    vtf.color = bDrawColored ? app2vs.color : float4(1, 1, 1, 1);

	return vtf;
}

VertexToFragment VS_main(ApplicationToVertex app2vs)
{
    VertexToFragment vtf = (VertexToFragment) 0;
    vtf.position = mul(viewProjection, float4(app2vs.position.xyz, 1.0f));
    vtf.color = bDrawColored ? app2vs.color : float4(1, 1, 1, 1);
    return vtf;
}

//----------------------------------------------------------------------------
// Geometry Shader
//----------------------------------------------------------------------------
[maxvertexcount(4)]
void GS_main(point VertexToGeometry input[1], inout TriangleStream<GeometryToFragmet> outStream)
{
	if (bUseUniformPointSize)
	{
        float fSizeX = (pointSize / viewport.x) / 4; //0.002;
        float fSizeY = (pointSize / viewport.y) / 4;

        GeometryToFragmet output;

		for (int i = 0; i < 4; i++)
		{
            float4 outPos = mul(float4(input[0].worldPosition, 1), view);
				output.position = mul(outPos, projection);

			// ideal wäre wenn die pixel positon genau auf ein pixel-zentrum fallen würde
			float2 l_vCurrScreenPosition = output.position.xy / output.position.w;
			float z = output.position.z / output.position.w;
			float2 l_vCurrPixelPosition = l_vCurrScreenPosition * viewport.xy * 0.5;
			int x = l_vCurrPixelPosition.x;
			int y = l_vCurrPixelPosition.y;
			l_vCurrPixelPosition.x = x + 0.5;// round(l_vCurrPixelPosition.x);
			l_vCurrPixelPosition.y = y + 0.5;//round(l_vCurrPixelPosition.y);

			// wie wärde die ideelae Bildschirmposition [0;1]?
			l_vCurrScreenPosition = l_vCurrPixelPosition * (1.0f / (viewport.xy / 2)) * output.position.w;

			// nochmal - jetzt idealle Positon verwenden, aber alte Tiefe beibehalten
			l_vCurrScreenPosition = output.position.xy / output.position.w;
			output.position.xy = l_vCurrScreenPosition;
			output.position.w = 1;
			output.position.z = z;

			// Pixel nach der Projektion vergrößern auf gewünschte größe

			float zoverNear = 1;//(outPos.z)/g_ClipPlanes.x;
			fSizeX = 1 / viewport.x * 2 * pointSize;
			fSizeY = 1 / viewport.y * 2 * pointSize;
			float4 posSize = float4(positions[i].x*fSizeX,
				positions[i].y*fSizeY,
				0,
				0);


			output.position += posSize;
			output.color = input[0].color; //float3(204.0/255,204.0/255,204.0/255);

			outStream.Append(output);
		}
	}
	else
	{
        GeometryToFragmet output;
        output.color = input[0].color;
        float4 pos = mul(viewProjection, float4(input[0].worldPosition, 1));
		for (int i = 0; i < 4; i++)
		{
			output.position = pos + float4(
				positions[i].x*pointSize * 0.0001,
				positions[i].y*pointSize * 0.0001,
				0,
				0);

            //output.position = mul(projection, output.position);
			outStream.Append(output);
		}
	}
	outStream.RestartStrip();
}


//----------------------------------------------------------------------------
// Pixel Shader
//----------------------------------------------------------------------------
FragmentToPixel PS_main_old(GeometryToFragmet gtf)
{
	FragmentToPixel final;

	final.color = float4(gtf.color.xyz, 1.0f);

	return final;
}

FragmentToPixel PS_main(VertexToFragment vtf)
{
    FragmentToPixel final;

    final.color = float4(vtf.color.xyz, 1.0f);

    return final;
}