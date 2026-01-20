//------  Descriptor_Heap.cpp  ------
//------  参照  ------
#include"Descriptor_Heap.h"
#include<cassert>


//@brief	---  ディスクリプターヒープ作成関数  ---
//@return	ディスクリプターヒープの作成可否
[[nodiscard]] bool DescriptorHeap :: Create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible)noexcept {

	//
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Type			= type;
	desc.NumDescriptors = numDescriptors;
	desc.Flags			= shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	Type_ = type;

	const auto hr = Device::Instance().Get()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&Heap_));
	if (FAILED(hr)) {
		assert(false && "ディスクリプターヒープ作成失敗");
		return false;
	}

	for (int i = 0; i < numDescriptors; i++) {
		FreeID_.push_back(i);
	}

	return true;
}

//@brief	---  ディスクリプターヒープ取得関数  ---
//@return	ディスクリプターヒープのポインター
[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap :: GetHeap()const noexcept {
	assert(Heap_ && "ディスクリプターヒープ未作成");
	return Heap_.Get();
}

//@brief	---  ディスクリプターヒープタイプ取得関数  ---
//@return	ディスクリプターヒープタイプ
[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeap :: GetType()const noexcept {
	assert(Heap_ && "ディスクリプターヒープ未作成");
	return Type_;
}

//@brief	---  ディスクリプターヒープ確保関数  ---
//@return	確保したディスクリプターヒープの番号
[[nodiscard]] std::optional<UINT> DescriptorHeap :: AllocateDescriptor() noexcept {
	if (FreeID_.empty()) {
		return std::nullopt;
	}
	const auto index = FreeID_.back();
	FreeID_.pop_back();
	return index;
}

//@brief	---  ディスクリプターヒープ解放登録関数  ---
void DescriptorHeap :: ReleaseDescriptor(UINT Index) noexcept {
	ApplyPendingID_.push_back(Index);
}

//@brief	---  ディスクリプターヒープ解放関数  ---
void DescriptorHeap :: ApplyPending()noexcept {
	if(ApplyPendingID_.empty()) {
		return;
	}

	for (auto i : ApplyPendingID_) {
		FreeID_.push_back(i);
	}
	ApplyPendingID_.clear();
}