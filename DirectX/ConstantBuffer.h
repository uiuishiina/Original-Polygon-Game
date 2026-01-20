#pragma once
//------  ConstantBuffer.h  ------
//------  参照  ------
#include"Device.h"
#include"../GameManager/DescriptorManager.h"



//@brief	------  コンスタントバッファ制御クラス  ------
class ConstantBuffer final
{
public:
	ConstantBuffer() = default;
	~ConstantBuffer() {
		DHManager::Instance().ReleaseDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, Index_);
	}

	//@brief	---  コンスタントバッファ作成関数  ---
	//@param	ディスクリプターヒープ
	//@param	作成するバッファのメモリサイズ
	//@param	作成するバッファの位置指定
	//@return	コンスタントバッファの作成可否
	[[nodiscard]] bool Create(UINT BufferSize_)noexcept;

	//@brief	---  コンスタントバッファ取得関数  ---
	//@return	コンスタントバッファポインター
	[[nodiscard]] ID3D12Resource* Get()const noexcept;

	//@brief	---  GPUディスクリプタハンドル取得関数  ---
	//@return	GPUハンドル
	[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE GetHandle()const noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12Resource> ConstantBuffer_{};	//コンスタントバッファ
	D3D12_GPU_DESCRIPTOR_HANDLE				GPUHandle_{};		//GPUハンドル
	UINT Index_;
};