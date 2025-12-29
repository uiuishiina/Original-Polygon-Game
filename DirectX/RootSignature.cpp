//------  RootSIgnature.cpp  ------
//------  参照  ------
#include"RootSignature.h"
#include<cassert>


//@brief	---  ルートシグネチャ作成関数  ---
//@return	ルートシグネチャの作成可否
[[nodiscard]] bool RootSignature :: Create()noexcept {

	// 描画に必要なリソースを設定
	D3D12_ROOT_SIGNATURE_DESC desc{};
	desc.NumParameters		= 0;
	desc.pParameters		= nullptr;
	desc.NumStaticSamplers	= 0;
	desc.pStaticSamplers	= nullptr;
	desc.Flags				= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//ルートシグネチャをシリアライズ
	ID3DBlob* S{};
	auto hr = D3D12SerializeRootSignature(
		&desc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&S,
		nullptr
	);
	if (FAILED(hr)) {
		assert(false && "ルートシグネチャのシリアライズ化失敗");
		return false;
	}
	
	hr = Device::Instance().Get()->CreateRootSignature(
		0,
		S->GetBufferPointer(),
		S->GetBufferSize(),
		IID_PPV_ARGS(&RootSignature_)
	);
	if (FAILED(hr)) {
		assert(false && "ルートシグネチャ作成失敗");
		return false;
	}
	if (S) {
		S->Release();
	}
	return true;
}

//@brief	---  ルートシグネチャ取得関数  ---
//@return	ルートシグネチャのポインター
[[nodiscard]] ID3D12RootSignature* RootSignature :: Get()const noexcept {
	assert(RootSignature_ && "ルートシグネチャ未作成");
	return RootSignature_.Get();
}