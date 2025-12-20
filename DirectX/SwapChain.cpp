//------  SwapChain.cpp  ------
//------  参照  ------
#include"SwapChain.h"
#include<cassert>

//デストラクタ
SwapChain :: ~SwapChain() {
	if (SwapChain_) {
		SwapChain_->Release();
		SwapChain_ = nullptr;
	}
}

//@brief	---  スワップチェイン作成関数  ---
//@return	スワップチェイン作成可否
[[nodiscard]] bool SwapChain :: Create(const DXGI& DXGI, const CommandQueue& Queue, const Window& Window)noexcept {

	const auto [w, h] = Window.GetSize();

	//スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC1 desc{};
	desc.BufferCount		= 2;
	desc.Width				= w;
	desc.Height				= h;
	desc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.SwapEffect			= DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.SampleDesc.Count	= 1;

	//一時スワップチェイン作成
	IDXGISwapChain1* temp{};
	{
		const auto hr = DXGI.GetFactory()->CreateSwapChainForHwnd(Queue.Get(), Window.GetHandle(),
			&desc, nullptr, nullptr, &temp);
		if (FAILED(hr)) {
			assert(false && "スワップチェイン作成失敗");
			return false;
		}
	}
	//hrが使いたいためスコープに入れる
	{
		//スワップチェインアップグレード
		const auto hr = temp->QueryInterface(IID_PPV_ARGS(&SwapChain_));
		if (FAILED(hr)) {
			assert(false && "スワップチェインアップグレード失敗");
			return false;
		}
	}
	return true;
}

//@brief	---  スワップチェインポインター取得関数  ---
//@return	スワップチェインポインター
[[nodiscard]] IDXGISwapChain3* SwapChain :: Get()const noexcept {
	if (!SwapChain_) {
		assert(false && "スワップチェイン未作成");
		return nullptr;
	}
	return SwapChain_;
}