#pragma once
//------  RenderTarget.h  ------
//------  参照  ------
#include"Device.h"
#include"SwapChain.h"
#include"../GameManager/DescriptorManager.h"
#include<vector>

//@brief	------  レンダーターゲット制御クラス  ------
class RenderTarget final
{
public:
	RenderTarget() = default;
	//デストラクタ
	~RenderTarget() = default;

	//@brief	--- レンダーターゲット作成関数  ---
	//@return	レンダーターゲットの作成可否
	[[nodiscard]] bool Create(const SwapChain& Swap)noexcept;

	//@brief	---  ディスクリプタハンドル取得関数  ---
	//@return	ディスクリプタハンドル
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE GetHandle(UINT Index)const noexcept;

	//@brief	---  レンダーターゲット取得関数  ---
	//@return	レンダーターゲットのポインター
	[[nodiscard]] ID3D12Resource* Get(UINT Index)const noexcept;
private:
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> Rendertargets_;	//レンダーターゲット
};