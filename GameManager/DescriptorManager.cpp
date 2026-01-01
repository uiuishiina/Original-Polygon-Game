//------  DescriptorManager.cpp  ------
//------  参照  ------
#include"DescriptorManager.h"
#include<cassert>

//デストラクタ
DHManager :: ~DHManager() {
	Map_.clear();
}

//@breif	---  ディスクリプターヒープ作成指示関数  ---
//@return	ディスクリプターヒープの作成可否
[[nodiscard]] bool DHManager:: Create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible)noexcept {
	//作成済みか
	if (Map_.find(type) != Map_.end()) {
		return false;
	}

	//作成
	auto p = std::make_unique<DescriptorHeap>();
	if (p->Create(type, numDescriptors, shaderVisible)) {
		Map_.emplace(type, std::move(p));
	}
	return true;
}

//@brief	---  ディスクリプターヒープ確保関数  ---
//@return	確保したディスクリプターヒープの番号
[[nodiscard]] UINT DHManager:: AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept {
	const auto it = Map_.find(type);
	if (it == Map_.end()) {
		assert(false && "ディスクリプタヒープ取得失敗(タイプ)");
	}
	const auto value = it->second->AllocateDescriptor();
	assert(value.has_value() && "ディスクリプタヒープ取得失敗(番号)");

	return value.value();
}

//@brief	---  ディスクリプターヒープ取得関数  ---
//@return	ディスクリプターヒープアドレス
[[nodiscard]] ID3D12DescriptorHeap* DHManager:: Get(D3D12_DESCRIPTOR_HEAP_TYPE type) const noexcept {
	const auto it = Map_.find(type);
	if (it == Map_.end()) {
		assert(false && "ディスクリプタヒープ取得失敗(タイプ)");
		return nullptr;
	}
	return it->second->GetHeap();
}