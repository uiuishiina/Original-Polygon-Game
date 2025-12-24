#pragma once
//------  SwapChain.h  ------
//------  参照  ------
#include"DXGI.h"
#include"CommandQueue.h"
#include"../Window/Window.h"

//@brief	------  スワップチェイン制御クラス  ------
class SwapChain final
{
public:
	SwapChain() = default;
	//デストラクタ
	~SwapChain();

	//@brief	---  スワップチェイン作成関数  ---
	//@return	スワップチェインの作成可否
	[[nodiscard]] bool Create(const DXGI& DXGI, const CommandQueue& Queue, const Window& Window)noexcept;

	//@brief	---  スワップチェインポインター取得関数  ---
	//@return	スワップチェインのポインター
	[[nodiscard]] IDXGISwapChain3* Get()const noexcept;

	//@brief	---  スワップチェイン設定取得  ---
	//@return	スワップチェインの設定
	[[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& GetDesc()const noexcept;
private:
	IDXGISwapChain3* SwapChain_{};	//スワップチェイン
	DXGI_SWAP_CHAIN_DESC1 Desc_{};	//スワップチェイン設定
};