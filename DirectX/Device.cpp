//------  Device.cpp  ------
//------  参照  ------
#include"Device.h"
#include<cassert>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")

//デストラクタ
Device :: ~Device() {
	if (Device_) {
		Device_->Release();
		Device_ = nullptr;
	}
}

//@brief	---  デバイス作成関数  ---
//@return	デバイス作成の成否
[[nodiscard]] bool Device :: Create(const DXGI& DXGI)noexcept {
	const auto hr = D3D12CreateDevice(DXGI.GetAdaptor(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&Device_));
	if (FAILED(hr)) {
		assert(false && "デバイス作成失敗");
		return false;
	}
	return true;
}

//@brief	---  デバイスポインター取得関数  ---
//@return	デバイスポインター
[[nodiscard]] ID3D12Device* Device :: Get()const noexcept {
	if (!Device_) {
		assert(false && "デバイス未作成");
		return nullptr;
	}
	return Device_;
}