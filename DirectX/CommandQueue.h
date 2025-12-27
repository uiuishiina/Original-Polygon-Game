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
	~CommandQueue() = default;

	//@brief	---  コマンドキュー作成関数  ---
	//@return	コマンドキュー作成の成否
	[[nodiscard]] bool Create()noexcept;

	//@brief	---  コマンドキュー取得関数  ---
	//@return	コマンドキューのポインター
	[[nodiscard]] ID3D12CommandQueue* Get()const noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12CommandQueue> CommandQueue_{};	//コマンドキュー
};