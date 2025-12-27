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
	return true;
}

//@brief	---  ディスクリプターヒープ取得関数  ---
//@return	ディスクリプターヒープのポインター
[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap :: GetHeap()const noexcept {
	if (!Heap_) {
		assert(false && "ディスクリプターヒープ未作成");
		return nullptr;
	}
	return Heap_.Get();
}

//@brief	---  ディスクリプターヒープタイプ取得関数  ---
//@return	ディスクリプターヒープタイプ
[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeap :: GetType()const noexcept {
	if (!Heap_) {
		assert(false && "ディスクリプターヒープ未作成");
	}
	return Type_;
}