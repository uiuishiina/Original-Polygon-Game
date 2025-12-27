#pragma once
//------  DXGI.h  ------
//------  参照  ------
#include<d3d12.h>
#include<dxgi1_4.h>
#include <wrl/client.h>

//@brief	------  DXGI制御クラス  ------
class DXGI final 
{
public:
	DXGI() = default;
	~DXGI() = default;

	//@brief	---  ディスプレイアダプター設定関数  ---
	//@return	ディスプレイの設定の可否
	[[nodiscard]] bool SetDisplayAdapter()noexcept;

	//@brief	---  DXGIファクトリー取得関数  ---
	//@return	ファクトリーのポインター
	[[nodiscard]] IDXGIFactory4* GetFactory()const noexcept;

	//@brief	---  ディスプレイアダプター取得関数  ---
	//@return	アダプターのポインター
	[[nodiscard]] IDXGIAdapter1* GetAdaptor()const noexcept;
private:
	Microsoft::WRL::ComPtr <IDXGIFactory4> dxgiFactory_{};	//DXGI作成ファクトリー
	Microsoft::WRL::ComPtr <IDXGIAdapter1> dxgiAdapter_{};	//アダプター
};