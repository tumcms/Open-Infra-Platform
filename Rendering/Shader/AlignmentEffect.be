<?xml version="1.0" encoding="utf-8"?>

<effect>
	<pipelinestate name="lineStrip">
		<D3D11>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_line"/>
			<GeometryShader filename="D3D/AlignmentShader.hlsl" entry="GS_lineStrip"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_line"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_line"/>
			<GeometryShader filename="D3D/AlignmentShader.hlsl" entry="GS_lineStrip"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_line"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="lineList">
		<D3D11>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_line"/>
			<GeometryShader filename="D3D/AlignmentShader.hlsl" entry="GS_lineList"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_line"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_line"/>
			<GeometryShader filename="D3D/AlignmentShader.hlsl" entry="GS_lineList"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_line"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="triangleList">
		<D3D11>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_solid"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_solid"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_solid"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_solid"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="pickLineStrip">
		<D3D11>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_line_pick"/>
			<GeometryShader filename="D3D/AlignmentShader.hlsl" entry="GS_lineStrip"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_line_pick"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_line_pick"/>
			<GeometryShader filename="D3D/AlignmentShader.hlsl" entry="GS_lineStrip"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_line_pick"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="pickLineList">
		<D3D11>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_line_pick"/>
			<GeometryShader filename="D3D/AlignmentShader.hlsl" entry="GS_lineList"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_line_pick"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_line_pick"/>
			<GeometryShader filename="D3D/AlignmentShader.hlsl" entry="GS_lineList"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_line_pick"/>
		</D3D12>
	</pipelinestate>
	<pipelinestate name="pickTriangleList">
		<D3D11>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_solid"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_solid_pick"/>
		</D3D11>
		<D3D12>
			<VertexShader filename="D3D/AlignmentShader.hlsl" entry="VS_solid"/>
			<PixelShader filename="D3D/AlignmentShader.hlsl" entry="PS_solid_pick"/>
		</D3D12>
	</pipelinestate>
</effect>