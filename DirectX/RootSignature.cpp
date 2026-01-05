//------  RootSIgnature.cpp  ------
//------  参照  ------
#include"RootSignature.h"
#include<cassert>


//@brief	---  ルートシグネチャ作成関数  ---
//@return	ルートシグネチャの作成可否
[[nodiscard]] bool RootSignature :: Create()noexcept {

	//コンスタントバッファ0作成
	D3D12_DESCRIPTOR_RANGE r0{};
	r0.RangeType			= D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	r0.NumDescriptors		= 1;
	r0.BaseShaderRegister	= 0;
	r0.RegisterSpace		= 0;
	r0.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//コンスタントバッファ1作成
	D3D12_DESCRIPTOR_RANGE r1{};
	r1.RangeType			= D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	r1.NumDescriptors		= 1;
	r1.BaseShaderRegister	= 1;
	r1.RegisterSpace		= 0;
	r1.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//ルートパラメーター設定
	constexpr auto pNum = 2;
	D3D12_ROOT_PARAMETER RootP[pNum]{};
	RootP[0].ParameterType							= D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	RootP[0].ShaderVisibility						= D3D12_SHADER_VISIBILITY_VERTEX;  // 頂点シェーダーのみで利用する
	RootP[0].DescriptorTable.NumDescriptorRanges	= 1;
	RootP[0].DescriptorTable.pDescriptorRanges		= &r0;
	RootP[1].ParameterType							= D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	RootP[1].ShaderVisibility						= D3D12_SHADER_VISIBILITY_VERTEX;  // すべてのシェーダーで利用する
	RootP[1].DescriptorTable.NumDescriptorRanges	= 1;
	RootP[1].DescriptorTable.pDescriptorRanges		= &r1;

	// 描画に必要なリソースを設定
	D3D12_ROOT_SIGNATURE_DESC desc{};
	desc.NumParameters		= pNum;
	desc.pParameters		= RootP;
	desc.NumStaticSamplers	= 0;
	desc.pStaticSamplers	= nullptr;
	desc.Flags				= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	//ルートシグネチャをシリアライズ
	ID3DBlob* S{};
	ID3DBlob* Error{};
	auto hr = D3D12SerializeRootSignature(
		&desc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&S,
		&Error
	);
	if (FAILED(hr)) {
		char* p = static_cast<char*>(Error->GetBufferPointer());
		assert(false && "ルートシグネチャシリアライズ化失敗");
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
		S->Release();}
	if (Error) {
		Error->Release();}
	return true;
}

//@brief	---  ルートシグネチャ取得関数  ---
//@return	ルートシグネチャのポインター
[[nodiscard]] ID3D12RootSignature* RootSignature :: Get()const noexcept {
	assert(RootSignature_ && "ルートシグネチャ未作成");
	return RootSignature_.Get();
}