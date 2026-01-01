//------  RenderTarget.cpp  ------
//------  参照  ------
#include"RenderTarget.h"
#include<cassert>


//@brief	--- レンダーターゲット作成関数  ---
//@return	レンダーターゲットの作成可否
[[nodiscard]] bool RenderTarget :: Create(const SwapChain& Swap)noexcept {

	//スワップチェインの設定を取得
	const auto& desc = Swap.GetDesc();
	//配列のサイズ設定
	Rendertargets_.resize(desc.BufferCount);
	//ディスクリプターヒープのタイプを取得 
	auto h = DHManager::Instance().Get(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//ディスクリプターヒープの先頭を取得
	auto Handle = h->GetCPUDescriptorHandleForHeapStart();
	
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
		Handle.ptr += Device::Instance().Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}
	return true;
}

//@brief	---  ディスクリプタハンドル取得関数  ---
//@return	ディスクリプタハンドル
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget :: GetHandle(UINT Index)const noexcept {
	if (Index >= Rendertargets_.size() || !Rendertargets_[Index]) {
		assert(false && "レンダーターゲットエラー");
	}
	
	//ディスクリプターヒープのタイプを取得
	auto h = DHManager::Instance().Get(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	//ディスクリプターヒープの先頭を取得
	auto Handle = h->GetCPUDescriptorHandleForHeapStart();
	//ポインターを操作してハンドルを移動
	Handle.ptr += (Index * Device::Instance().Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
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