//------  RenderTarget.cpp  ------
//------  参照  ------
#include"RenderTarget.h"
#include<cassert>


//@brief	--- レンダーターゲット作成関数  ---
//@return	レンダーターゲットの作成可否
[[nodiscard]] bool RenderTarget :: Create(const SwapChain& Swap, const DescriptorHeap& Heap)noexcept {

	//スワップチェインの設定を取得
	const auto& desc = Swap.GetDesc();
	//配列のサイズ設定
	Rendertargets_.resize(desc.BufferCount);
	//ディスクリプターヒープの先頭を取得
	auto Handle = Heap.GetHeap()->GetCPUDescriptorHandleForHeapStart();
	//ディスクリプターヒープのタイプを取得
	auto Type = Heap.GetType();
	assert(Type == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプターヒープタイプ異常");
	//バッファの作成
	for (UINT i = 0; i < desc.BufferCount; i++) {
		const auto hr = Swap.Get()->GetBuffer(i, IID_PPV_ARGS(&Rendertargets_[i]));
		if (FAILED(hr)) {
			assert(false && "バッファの取得に失敗");
			return false;
		}
		//レンダーターゲットビューを作成しディスクリプターヒープと紐づけ
		Device::Instance().Get()->CreateRenderTargetView(Rendertargets_[i].Get(), nullptr, Handle);
		//ポインターを操作してハンドルを移動
		Handle.ptr += Device::Instance().Get()->GetDescriptorHandleIncrementSize(Type);
	}
	return true;
}

//@brief	---  ディスクリプタハンドル取得関数  ---
//@return	ディスクリプタハンドル
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget :: GetHandle(const DescriptorHeap& Heap, UINT Index)const noexcept {
	if (Index >= Rendertargets_.size() || !Rendertargets_[Index]) {
		assert(false && "レンダーターゲットエラー");
	}
	//ディスクリプターヒープの先頭を取得
	auto Handle = Heap.GetHeap()->GetCPUDescriptorHandleForHeapStart();
	//ディスクリプターヒープのタイプを取得
	auto Type = Heap.GetType();
	assert(Type == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプターヒープタイプ異常");
	//ポインターを操作してハンドルを移動
	Handle.ptr += (Index * Device::Instance().Get()->GetDescriptorHandleIncrementSize(Type));
	return Handle;
}

//@brief	---  レンダーターゲット取得関数  ---
//@return	レンダーターゲットのポインター
[[nodiscard]] ID3D12Resource* RenderTarget :: Get(UINT Index)const noexcept {
	if (Index >= Rendertargets_.size() || !Rendertargets_[Index]) {
		assert(false && "レンダーターゲットエラー");
		return nullptr;
	}
	return Rendertargets_[Index].Get();
}