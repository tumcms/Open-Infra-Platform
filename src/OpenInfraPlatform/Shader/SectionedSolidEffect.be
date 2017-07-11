<?xml version="1.0" encoding="utf-8"?>

<effect>
	<pipelinestate name="lineStrip">
		<D3D11>
			<VertexShader filename="D3D/SectionedSolidShader.hlsl" entry="VS_line"/>
			<GeometryShader filename="D3D/SectionedSolidShader.hlsl" entry="GS_line"/>
			<PixelShader filename="D3D/SectionedSolidShader.hlsl" entry="PS_line"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/SectionedSolidShader.hlsl" entry="VS_line"/>
			<GeometryShader filename="D3D/SectionedSolidShader.hlsl" entry="GS_line"/>
			<PixelShader filename="D3D/SectionedSolidShader.hlsl" entry="PS_line"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="triangleStrip">
		<D3D11>
			<VertexShader filename="D3D/SectionedSolidShader.hlsl" entry="VS_solid"/>
			<PixelShader filename="D3D/SectionedSolidShader.hlsl" entry="PS_solid"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/SectionedSolidShader.hlsl" entry="VS_solid"/>
			<PixelShader filename="D3D/SectionedSolidShader.hlsl" entry="PS_solid"/>
		</D3D12>
	</pipelinestate>
</effect>
