<?xml version="1.0" encoding="utf-8"?>

<effect>
	<pipelinestate name="default">
		<D3D11>
			<VertexShader filename="D3D/DEMShader.hlsl" entry="VS_main"/>
			<GeometryShader filename="D3D/DEMShader.hlsl" entry="GS_main"/>
			<PixelShader filename="D3D/DEMShader.hlsl" entry="PS_main"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/DEMShader.hlsl" entry="VS_main"/>
			<GeometryShader filename="D3D/DEMShader.hlsl" entry="GS_main"/>
			<PixelShader filename="D3D/DEMShader.hlsl" entry="PS_main"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="pick">
		<D3D11>
			<VertexShader filename="D3D/DEMShader.hlsl" entry="VS_main"/>
			<GeometryShader filename="D3D/DEMShader.hlsl" entry="GS_main"/>
			<PixelShader filename="D3D/DEMShader.hlsl" entry="PS_pick"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/DEMShader.hlsl" entry="VS_main"/>
			<GeometryShader filename="D3D/DEMShader.hlsl" entry="GS_main"/>
			<PixelShader filename="D3D/DEMShader.hlsl" entry="PS_pick"/>
		</D3D12>
	</pipelinestate>
</effect>