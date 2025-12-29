#pragma once
//------  ConstantBuffer.h  ------
//------  参照  ------
#include"Device.h"
#include"Descriptor_Heap.h"


//@brief	------  コンスタントバッファ制御クラス  ------
class ConstantBuffer final
{
public:
	ConstantBuffer() = default;
	~ConstantBuffer() = default;

	//@brief	---  コンスタントバッファ作成関数  ---
	//@param	ディスクリプターヒープ
	//@param	作成するバッファのメモリサイズ
	//@param	作成するバッファの位置指定
	//@return	コンスタントバッファの作成可否
	[[nodiscard]] bool Create(const DescriptorHeap& Heap, UINT BufferSize_, UINT Index)noexcept;

	//@brief	---  コンスタントバッファ取得関数  ---
	//@return	コンスタントバッファポインター
	[[nodiscard]] ID3D12Resource* Get()const noexcept;

	//@brief	---  GPUディスクリプタハンドル取得関数  ---
	//@return	GPUハンドル
	[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE GetHandle()const noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12Resource> ConstantBuffer_{};	//コンスタントバッファ
	D3D12_GPU_DESCRIPTOR_HANDLE				GPUHandle_{};		//GPUハンドル
};