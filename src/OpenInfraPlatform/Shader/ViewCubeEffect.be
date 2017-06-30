<?xml version="1.0" encoding="utf-8"?>

<effect>
  <pipelinestate name="cube">
    <D3D11>
      <VertexShader filename="D3D/ViewCubeEffect.hlsl" entry="VS_main"/>
      <PixelShader filename="D3D/ViewCubeEffect.hlsl" entry="PS_cube"/>
    </D3D11>
    <D3D12>
      <VertexShader filename="D3D/ViewCubeEffect.hlsl" entry="VS_main"/>
      <PixelShader filename="D3D/ViewCubeEffect.hlsl" entry="PS_cube"/>
    </D3D12>
  </pipelinestate>
  <pipelinestate name="pick">
    <D3D11>
      <VertexShader filename="D3D/ViewCubeEffect.hlsl" entry="VS_main"/>
      <PixelShader filename="D3D/ViewCubeEffect.hlsl" entry="PS_pick"/>
    </D3D11>
    <D3D12>
      <VertexShader filename="D3D/ViewCubeEffect.hlsl" entry="VS_main"/>
      <PixelShader filename="D3D/ViewCubeEffect.hlsl" entry="PS_pick"/>
    </D3D12>
  </pipelinestate>
</effect>