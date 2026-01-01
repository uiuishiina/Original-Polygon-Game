//------  PiplineState.cpp  ------
//------  参照  ------
#include"PiplineState.h"
#include<cassert>

//@brief	---  パイプラインステート作成関数  ---
//@return	パイプラインステートの作成可否
[[nodiscard]] bool Pipline :: Create(const CompileShader& shader, const RootSignature& root)noexcept {

	//頂点レイアウト設定
	D3D12_INPUT_ELEMENT_DESC Edesc[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0}
	};

	//デプスステート設定
	D3D12_DEPTH_STENCIL_DESC DDesc{};
	DDesc.DepthEnable			= true;
	DDesc.StencilEnable			= false;
	DDesc.DepthWriteMask		= D3D12_DEPTH_WRITE_MASK_ALL;
	DDesc.DepthFunc				= D3D12_COMPARISON_FUNC_LESS;

	// ブレンドステート
   // 描画結果の合成方法を設定する
	D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
	renderTargetBlendDesc.BlendEnable = true;
	// RGB 合成
	renderTargetBlendDesc.SrcBlend	= D3D12_BLEND_SRC_ALPHA;
	renderTargetBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	renderTargetBlendDesc.BlendOp	= D3D12_BLEND_OP_ADD;
	// アルファ合成
	renderTargetBlendDesc.SrcBlendAlpha		= D3D12_BLEND_ONE;
	renderTargetBlendDesc.DestBlendAlpha	= D3D12_BLEND_ZERO;
	renderTargetBlendDesc.BlendOpAlpha		= D3D12_BLEND_OP_ADD;
	// 書き込み対象のチャンネルを指定
	renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
	// 設定可能な全てのレンダーターゲットに同じ設定を適用する
	D3D12_BLEND_DESC blendDesc{};
	for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
		blendDesc.RenderTarget[i] = renderTargetBlendDesc;
	}

	//ラスタライザステート設定
	D3D12_RASTERIZER_DESC Rdesc{};
	Rdesc.FillMode				= D3D12_FILL_MODE_SOLID;
	Rdesc.CullMode				= D3D12_CULL_MODE_NONE;
	Rdesc.FrontCounterClockwise = false;
	Rdesc.DepthBias				= D3D12_DEFAULT_DEPTH_BIAS;
	Rdesc.DepthBiasClamp		= D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	Rdesc.SlopeScaledDepthBias	= D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	Rdesc.DepthClipEnable		= true;
	Rdesc.MultisampleEnable		= false;
	Rdesc.AntialiasedLineEnable = false;
	Rdesc.ForcedSampleCount		= 0;
	Rdesc.ConservativeRaster	= D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	// パイプラインステート
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc{};
	psoDesc.InputLayout					= { Edesc, _countof(Edesc) };
	psoDesc.pRootSignature				= root.Get();
	psoDesc.VS							= { shader.GetVertex()->GetBufferPointer(), shader.GetVertex()->GetBufferSize() };
	psoDesc.PS							= { shader.GetPixel()->GetBufferPointer(), shader.GetPixel()->GetBufferSize() };
	psoDesc.RasterizerState				= Rdesc;
	psoDesc.BlendState					= blendDesc;
	psoDesc.DepthStencilState			= DDesc;
	psoDesc.SampleMask					= UINT_MAX;
	psoDesc.PrimitiveTopologyType		= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets			= 1;
	psoDesc.RTVFormats[0]				= DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count			= 1;
	auto hr = Device::Instance().Get()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&State_));
	if (FAILED(hr)) {
		assert(false && "パイプラインステート作成失敗");
	}

	return true;
}


//@brief	--- パイプラインステート取得関数  ---
//@return	パイプラインステートのポインター
[[nodiscard]] ID3D12PipelineState* Pipline :: Get()const noexcept {
	assert(State_ && "パイプラインステート未作成");
	return State_.Get();
}