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
	
	//ラスタライザステート設定
	D3D12_RASTERIZER_DESC Rdesc{};
	Rdesc.FillMode				= D3D12_FILL_MODE_SOLID;
	Rdesc.CullMode				= D3D12_CULL_MODE_BACK;
	Rdesc.FrontCounterClockwise = false;
	Rdesc.DepthBias				= D3D12_DEFAULT_DEPTH_BIAS;
	Rdesc.DepthBiasClamp		= D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	Rdesc.SlopeScaledDepthBias	= D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	Rdesc.DepthClipEnable		= true;
	Rdesc.MultisampleEnable		= false;
	Rdesc.AntialiasedLineEnable = false;
	Rdesc.ForcedSampleCount		= 0;
	Rdesc.ConservativeRaster	= D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	//ブレンドステート設定
	const D3D12_RENDER_TARGET_BLEND_DESC defaultBlendDesc = {
		FALSE,
		FALSE,
		D3D12_BLEND_ONE,
		D3D12_BLEND_ZERO,
		D3D12_BLEND_OP_ADD,
		D3D12_BLEND_ONE,
		D3D12_BLEND_ZERO,
		D3D12_BLEND_OP_ADD,
		D3D12_LOGIC_OP_NOOP,
		D3D12_COLOR_WRITE_ENABLE_ALL,
	};
	D3D12_BLEND_DESC Bdesc{};
	Bdesc.AlphaToCoverageEnable = false;
	Bdesc.IndependentBlendEnable = false;
	for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
		Bdesc.RenderTarget[i] = defaultBlendDesc;
	}


	// パイプラインステート
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc{};
	psoDesc.InputLayout					= { Edesc, _countof(Edesc) };
	psoDesc.pRootSignature				= root.Get();
	psoDesc.VS							= { shader.GetVertex()->GetBufferPointer(), shader.GetVertex()->GetBufferSize() };
	psoDesc.PS							= { shader.GetPixel()->GetBufferPointer(), shader.GetPixel()->GetBufferSize() };
	psoDesc.RasterizerState				= Rdesc;
	psoDesc.BlendState					= Bdesc;
	psoDesc.DepthStencilState.DepthEnable = false;
	psoDesc.DepthStencilState.StencilEnable = false;
	psoDesc.SampleMask					= UINT_MAX;
	psoDesc.PrimitiveTopologyType		= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets			= 1;
	psoDesc.RTVFormats[0]				= DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count			= 1;
	auto res = Device::Instance().Get()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&State_));
	if (FAILED(res)) {
		assert(false && "パイプラインステート作成失敗");
	}

	return true;
}


//@brief	--- パイプラインステート取得関数  ---
//@return	パイプラインステートのポインター
[[nodiscard]] ID3D12PipelineState* Pipline :: Get()const noexcept {
	if (!State_) {
		assert(false && "パイプラインステート未作成");
		return nullptr;
	}
	return State_.Get();
}