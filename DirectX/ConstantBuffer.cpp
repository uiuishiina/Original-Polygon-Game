//------  ConstantBuffer.cpp  ------
//------  参照  ------
#include"ConstantBuffer.h"
#include<cassert>


//@brief	---  コンスタントバッファ作成関数  ---
//@param	ディスクリプターヒープ
//@param	作成するバッファのメモリサイズ
//@param	作成するバッファの位置指定
//@return	コンスタントバッファの作成可否
[[nodiscard]] bool ConstantBuffer :: Create(UINT BufferSize_)noexcept {

	//アラインメント後のサイズ計算
	const auto size = (sizeof(BufferSize_) + 255) & ~255;

    // バッファリソース作成
    D3D12_HEAP_PROPERTIES heapProps{};
    heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
    D3D12_RESOURCE_DESC resourceDesc{};
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Width = size;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

    const auto hr = Device::Instance().Get()->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&ConstantBuffer_)
    );
    if(FAILED(hr)) {
        assert(false && "コンスタントバッファ作成失敗");
        return false;
    }

    //ビュー作成
    auto Index = DHManager::Instance().AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    auto heap = DHManager::Instance().Get(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

    //コンスタントバッファビュー設定
    D3D12_CONSTANT_BUFFER_VIEW_DESC Desc{};
    Desc.BufferLocation = ConstantBuffer_->GetGPUVirtualAddress();
    Desc.SizeInBytes = size;

    //ディスクリプタのサイズ取得
    const auto Descriptorsize = Device::Instance().Get()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    //ディスクリプターヒープ先頭アドレス取得
    auto CPUHandle = heap->GetCPUDescriptorHandleForHeapStart();
    //アドレスを指定分移動
    CPUHandle.ptr += Index * Descriptorsize;
    //コンスタントバッファビューとディスクリプターヒープを紐づけ
    Device::Instance().Get()->CreateConstantBufferView(&Desc, CPUHandle);
    //ディスクリプタハンドル保存
    GPUHandle_ = heap->GetGPUDescriptorHandleForHeapStart();
    GPUHandle_.ptr += Index * Descriptorsize;

    return true;
}

//@brief	---  コンスタントバッファ取得関数  ---
//@return	コンスタントバッファポインター
[[nodiscard]] ID3D12Resource* ConstantBuffer :: Get()const noexcept {
    assert(ConstantBuffer_ && "コンスタントバッファ未作成");
    return ConstantBuffer_.Get();
}

//@brief	---  GPUディスクリプタハンドル取得関数  ---
//@return	GPUハンドル
[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE ConstantBuffer :: GetHandle()const noexcept {
    assert(ConstantBuffer_ && "コンスタントバッファ未作成");
    return GPUHandle_;
}