#pragma once
//------  CommandQueue.h  ------
//------  参照  ------
#include"Device.h"

//@brief	------  コマンドキュー制御クラス  ------
class CommandQueue final
{
public:
	CommandQueue() = default;
	//デストラクタ
	~CommandQueue();

	//@brief	---  コマンドキュー作成関数  ---
	//@return	コマンドキュー作成の成否
	[[nodiscard]] bool Create(const Device& Device)noexcept;

	//@brief	---  コマンドキュー取得関数  ---
	//@return	コマンドキューのポインター
	[[nodiscard]] ID3D12CommandQueue* Get()const noexcept;
private:
	ID3D12CommandQueue* CommandQueue_{};	//コマンドキュー
};