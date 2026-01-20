#pragma once
//------  Descriptor_Heap.h  ------
//------  参照  ------
#include"Device.h"
#include <optional>
#include<vector>

//@brief	------  ディスクリプターヒープ作成クラス  ------
class DescriptorHeap final
{
public:
	DescriptorHeap() = default;
	~DescriptorHeap() = default;

	//@brief	---  ディスクリプターヒープ作成関数  ---
	//@return	ディスクリプターヒープの作成可否
	[[nodiscard]] bool Create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible = false)noexcept;

	//@brief	---  ディスクリプターヒープ取得関数  ---
	//@return	ディスクリプターヒープのポインター
	[[nodiscard]] ID3D12DescriptorHeap* GetHeap()const noexcept;

	//@brief	---  ディスクリプターヒープタイプ取得関数  ---
	//@return	ディスクリプターヒープタイプ
	[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE GetType()const noexcept;

	//@brief	---  ディスクリプターヒープ確保関数  ---
	//@return	確保したディスクリプターヒープの番号
	[[nodiscard]] std::optional<UINT> AllocateDescriptor() noexcept;

	//@brief	---  ディスクリプターヒープ解放登録関数  ---
	void ReleaseDescriptor(UINT Index) noexcept;

	//@brief	---  ディスクリプターヒープ解放関数  ---
	void ApplyPending()noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12DescriptorHeap>		Heap_{};	//	ディスクリプターヒープ
	D3D12_DESCRIPTOR_HEAP_TYPE							Type_{};	//	ディスクリプターヒープタイプ
	std::vector<UINT>									FreeID_{};	//	ディスクリプターヒープ番号
	std::vector<UINT>									DeleteID_{};//	ディスクリプターヒープ番号
	std::vector<UINT>									ApplyPendingID_{};//	ディスクリプターヒープ番号
};