//------  Device.cpp  ------
//------  参照  ------
#include"Device.h"
#include<cassert>
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxguid.lib")


//@brief	---  デバイス作成関数  ---
//@return	デバイス作成の成否
[[nodiscard]] bool Device :: Create()noexcept {

	//DXGI作成
	if (!DXGI_.SetDisplayAdapter()) {
		assert(false && "DXGI作成失敗");
		return false;
	}

	const auto hr = D3D12CreateDevice(DXGI_.GetAdaptor(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&Device_));
	if (FAILED(hr)) {
		assert(false && "デバイス作成失敗");
		return false;
	}
	return true;
}

//@brief	---  デバイスポインター取得関数  ---
//@return	デバイスポインター
[[nodiscard]] ID3D12Device* Device :: Get()const noexcept {
	assert(Device_ && "デバイス未作成");
	return Device_.Get();
}

//@brief	---  DXGI取得関数  ---
//@return	DXGIインスタンス
[[nodiscard]] const DXGI& Device :: GetDXGI()const noexcept {
	return DXGI_;
}