#pragma once
//------  Fence.h  ------
//------  参照  ------
#include"Device.h"

//@brief	------  フェンス制御クラス  ------
class Fence final 
{
public:
	Fence() = default;
	//デストラクタ
	~Fence();

	//@brief	---  フェンス作成関数  ---
	//@return	フェンスの作成可否
	[[nodiscard]] bool Create(const Device& Device)noexcept;

	//@brief	---  同期待機関数  ---
	void Wait(UINT64 Value)const noexcept;

	//@brief	---  フェンス取得関数  ---
	[[nodiscard]] ID3D12Fence* Get()const noexcept;
private:
	ID3D12Fence*	Fence_{};			//フェンス
	HANDLE			WaitGPUEvent_{};	//GPUとCPUの同期用イベント
};