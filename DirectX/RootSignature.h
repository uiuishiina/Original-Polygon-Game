#pragma once
//------  RootSignature.h  ------
//------  参照  ------
#include"Device.h"

//@brief	------  ルートシグネチャ制御クラス  ------
class RootSignature final
{
public:
	RootSignature() = default;
	~RootSignature() = default;

	//@brief	---  ルートシグネチャ作成関数  ---
	//@return	ルートシグネチャの作成可否
	[[nodiscard]] bool Create()noexcept;

	//@brief	---  ルートシグネチャ取得関数  ---
	//@return	ルートシグネチャのポインター
	[[nodiscard]] ID3D12RootSignature* Get()const noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12RootSignature> RootSignature_{};	//ルートシグネチャ
};