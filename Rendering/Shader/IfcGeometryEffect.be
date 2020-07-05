<?xml version="1.0" encoding="utf-8"?>

<effect>
	<pipelinestate name="mesh">
		<D3D11>
			<VertexShader filename="D3D/IfcGeometryEffect.hlsl" entry="VS_main"/>
			<PixelShader filename="D3D/IfcGeometryEffect.hlsl" entry="PS_main"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/IfcGeometryEffect.hlsl" entry="VS_main"/>
			<PixelShader filename="D3D/IfcGeometryEffect.hlsl" entry="PS_main"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="polyline">
		<D3D11>
			<VertexShader filename="D3D/IfcGeometryEffect.hlsl" entry="VS_polyline"/>
			<PixelShader filename="D3D/IfcGeometryEffect.hlsl" entry="PS_polyline"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/IfcGeometryEffect.hlsl" entry="VS_polyline"/>
			<PixelShader filename="D3D/IfcGeometryEffect.hlsl" entry="PS_polyline"/>
		</D3D12>
	</pipelinestate>
</effect>