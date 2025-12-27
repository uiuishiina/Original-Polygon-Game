#pragma once
//------  Device.h  ------
//------  参照  ------
#include"DXGI.h"
#include<d3d12.h>

//@brief	------  デバイス制御クラス  ------
class Device final 
{
public:
	//@brief	---  デバイス取得  ---
	//@return	デバイスインスタンス
	static Device& Instance() {
		static Device instance;
		return instance;
	}

	//@brief	---  デバイス作成関数  ---
	//@return	デバイス作成の成否
	[[nodiscard]] bool Create()noexcept;

	//@brief	---  デバイスポインター取得関数  ---
	//@return	デバイスポインター
	[[nodiscard]] ID3D12Device* Get()const noexcept;

	//@brief	---  DXGI取得関数  ---
	//@return	DXGIインスタンス
	[[nodiscard]] const DXGI& GetDXGI()const noexcept;
private:
	Device() = default;
	~Device() = default;

	DXGI DXGI_{};
	Microsoft::WRL::ComPtr <ID3D12Device> Device_{};	//デバイス
};