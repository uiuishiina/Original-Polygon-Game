//------  DepthBuffer.cpp  ------
//------  参照  ------
#include"DepthBuffer.h"
#include<cassert>

//@brief	---  デプスバッファ作成関数  ---
//@return	デプスバッファの作成可否
[[nodiscard]] bool DepthBuffer :: Create()noexcept {
	//ウィンドウズサイズ取得
	const auto [w, h] = Window::Instance().GetSize();

    // デプスバッファ用のテクスチャリソースの作成
    D3D12_HEAP_PROPERTIES heap{};
    heap.Type = D3D12_HEAP_TYPE_DEFAULT;
    D3D12_RESOURCE_DESC Desc{};
    Desc.Dimension              = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    Desc.Width                  = w;
    Desc.Height                 = h;
    Desc.DepthOrArraySize       = 1;
    Desc.MipLevels              = 1;
    Desc.Format                 = DXGI_FORMAT_D32_FLOAT;
    Desc.SampleDesc.Count       = 1;
    Desc.SampleDesc.Quality     = 0;
    Desc.Layout                 = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    Desc.Flags                  = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

    // デプスバッファのクリア値の設定
    D3D12_CLEAR_VALUE clearValue{};
    clearValue.Format = Desc.Format;
    clearValue.DepthStencil.Depth = 1.0f;
    clearValue.DepthStencil.Stencil = 0;

    const auto hr = Device::Instance().Get()->CreateCommittedResource(
        &heap,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_DEPTH_WRITE,
        &clearValue,
        IID_PPV_ARGS(&Buffer_));
    if (FAILED(hr)) {
        assert(false && "デプスバッファ作成失敗");
        return false;
    }
    
    // ビューの作成
    auto Dheap = DHManager::Instance().Get(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

    // デプスビューの設定
    D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
    dsvDesc.Format = Desc.Format;
    dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
    dsvDesc.Flags = D3D12_DSV_FLAG_NONE;

    // ディスクリプタヒープの開始ハンドルを取得
    Handle_ = Dheap->GetCPUDescriptorHandleForHeapStart();
    // デプスビューの作成
    Device::Instance().Get()->CreateDepthStencilView(Buffer_.Get(), &dsvDesc, Handle_);

    return true;
}

//@brief	---  デプスバッファ取得関数  ---
//@return	デプスバッファのポインター
[[nodiscard]] ID3D12Resource* DepthBuffer :: Get()const noexcept {
    assert(Buffer_ && "デプスバッファ未作成(p)");
    return Buffer_.Get();
}

//@brief	---  ディスクリプタハンドル取得関数  ---
//@return	ディスクリプタハンドル
[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE DepthBuffer :: GetHandle()const noexcept {
    assert(Buffer_ && "デプスバッファ未作成(h)");
    return Handle_;
}