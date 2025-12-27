//------  DXGI.cpp  ------
//------  参照  ------
#include"DXGI.h"
#include<cassert>
#pragma comment(lib, "dxgi.lib")

//@brief	---  ディスプレイアダプター設定関数  ---
//@return	ディスプレイの設定の可否
[[nodiscard]] bool DXGI :: SetDisplayAdapter()noexcept {
	//デバックレイヤーオン
#if _DEBUG
	ID3D12Debug* debug;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug)))) {
		debug->EnableDebugLayer();
	}
#endif
	UINT createFactoryFlags = 0;
#if _DEBUG
	createFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;	//ビット演算子 or演算
#endif

	//DXGIファクトリー作成
	const auto hr = CreateDXGIFactory2(createFactoryFlags, IID_PPV_ARGS(&dxgiFactory_));
	if (FAILED(hr)) {
		assert(false && "DXGIファクトリーの作成に失敗");
		return false;
	}

	UINT select = 0;
	IDXGIAdapter1* Adapter{};

	//ディスプレイアダプター取得
	while (dxgiFactory_->EnumAdapters1(select, &Adapter) != DXGI_ERROR_NOT_FOUND) {

		DXGI_ADAPTER_DESC1 desc{};
		Adapter->GetDesc1(&desc);
		select++;

		//ソフトウェアアダプターなら除外
		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
			Adapter->Release();
			continue;
		}

		//DirectX12の動作確認
		if (FAILED(D3D12CreateDevice(Adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) {
			Adapter->Release();
			continue;
		}

		dxgiAdapter_ = Adapter;
		break;
	}
	if (!dxgiAdapter_) {
		assert(false && "アダプタの取得に失敗");
		return false;
	}
	return true;
}

//@brief	---  DXGIファクトリー取得関数  ---
//@return	ファクトリーのポインター
[[nodiscard]] IDXGIFactory4* DXGI :: GetFactory()const noexcept {
	if (!dxgiFactory_) {
		assert(false && "DXGIファクトリー未作成");
		return nullptr;
	}
	return dxgiFactory_.Get();
}

//@brief	---  ディスプレイアダプター取得関数  ---
//@return	アダプターのポインター
[[nodiscard]] IDXGIAdapter1* DXGI :: GetAdaptor()const noexcept {
	if (!dxgiAdapter_) {
		assert(false && "アダプター未作成");
		return nullptr;
	}
	return dxgiAdapter_.Get();
}