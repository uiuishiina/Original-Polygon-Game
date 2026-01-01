//------  SwapChain.cpp  ------
//------  参照  ------
#include"SwapChain.h"
#include<cassert>


//@brief	---  スワップチェイン作成関数  ---
//@return	スワップチェイン作成可否
[[nodiscard]] bool SwapChain :: Create(const CommandQueue& Queue)noexcept {

	const auto [w, h] = Window::Instance().GetSize();

	//スワップチェインの設定
	Desc_ = {};
	Desc_.BufferCount		= 2;
	Desc_.Width				= w;
	Desc_.Height			= h;
	Desc_.Format			= DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc_.BufferUsage		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	Desc_.SwapEffect		= DXGI_SWAP_EFFECT_FLIP_DISCARD;
	Desc_.SampleDesc.Count	= 1;

	//一時スワップチェイン作成
	IDXGISwapChain1* temp{};
	{
		const auto hr = Device::Instance().GetDXGI().GetFactory()->CreateSwapChainForHwnd(Queue.Get(), Window::Instance().GetHandle(),
			&Desc_, nullptr, nullptr, &temp);
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
	assert(SwapChain_ && "スワップチェイン未作成");
	return SwapChain_.Get();
}

//@brief	---  スワップチェイン設定取得  ---
//@return	スワップチェインの設定
[[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& SwapChain :: GetDesc()const noexcept {
	assert(SwapChain_ && "スワップチェイン未作成");
	return Desc_;
}