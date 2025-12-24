#pragma once
//------  Descriptor_Heap.h  ------
//------  参照  ------
#include"Device.h"

//@brief	------  ディスクリプターヒープ制御クラス  ------
class DescriptorHeap final
{
public:
	DescriptorHeap() = default;
	//デストラクタ
	~DescriptorHeap();

	//@brief	---  ディスクリプターヒープ作成関数  ---
	//@return	ディスクリプターヒープの作成可否
	[[nodiscard]] bool Create(const Device& Device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible = false)noexcept;

	//@brief	---  ディスクリプターヒープ取得関数  ---
	//@return	ディスクリプターヒープのポインター
	[[nodiscard]] ID3D12DescriptorHeap* GetHeap()const noexcept;

	//@brief	---  ディスクリプターヒープタイプ取得関数  ---
	//@return	ディスクリプターヒープタイプ
	[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE GetType()const noexcept;
private:
	ID3D12DescriptorHeap*		Heap_{};	//	ディスクリプターヒープ
	D3D12_DESCRIPTOR_HEAP_TYPE	Type_{};	//	ディスクリプターヒープタイプ
};