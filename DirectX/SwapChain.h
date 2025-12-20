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
	//@return	スワップチェイン作成可否
	[[nodiscard]] bool Create(const DXGI& DXGI, const CommandQueue& Queue, const Window& Window)noexcept;

	//@brief	---  スワップチェインポインター取得関数  ---
	//@return	スワップチェインポインター
	[[nodiscard]] IDXGISwapChain3* Get()const noexcept;
private:
	IDXGISwapChain3* SwapChain_{};
};