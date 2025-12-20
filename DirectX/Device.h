#pragma once
//------  Device.h  ------
//------  参照  ------
#include"DXGI.h"
#include<d3d12.h>

//@brief	------  デバイス制御クラス  ------
class Device final 
{
public:
	Device() = default;
	//デストラクタ
	~Device();

	//@brief	---  デバイス作成関数  ---
	//@return	デバイス作成の成否
	[[nodiscard]] bool Create(const DXGI& DXGI)noexcept;

	//@brief	---  デバイスポインター取得関数  ---
	//@return	デバイスポインター
	[[nodiscard]] ID3D12Device* Get()const noexcept;
private:
	ID3D12Device* Device_{};	//デバイス
};