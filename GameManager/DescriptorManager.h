#pragma once
//------  DescriptorManager.h  ------
//------  参照  ------
#include"../DirectX/Descriptor_Heap.h"
#include <d3d12.h>
#include <unordered_map>
#include <memory>

//@brief	------  ディスクリプターヒープ制御クラス  ------
class DHManager final
{
public:
	//@brief	---  インスタンス取得関数  ---
	//@return	インスタンス
	static DHManager& Instance()noexcept {
		static DHManager container;
		return container;
	}

	//@breif	---  ディスクリプターヒープ作成指示関数  ---
	//@return	ディスクリプターヒープの作成可否
	[[nodiscard]] bool Create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible = false)noexcept;

	//@brief	---  ディスクリプターヒープ確保関数  ---
	//@return	確保したディスクリプターヒープの番号
	[[nodiscard]] UINT AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept;

	//@brief	---  ディスクリプターヒープ取得関数  ---
	//@return	ディスクリプターヒープアドレス
	[[nodiscard]] ID3D12DescriptorHeap* Get(D3D12_DESCRIPTOR_HEAP_TYPE type) const noexcept;

private:
	DHManager() = default;
	~DHManager();
	std::unordered_map<UINT, std::unique_ptr<DescriptorHeap>> Map_{};  /// 種類毎のデスクリプタマップ
};