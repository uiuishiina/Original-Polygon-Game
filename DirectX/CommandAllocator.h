#pragma once
//------  CommandAllocator.h  ------
//------  参照  ------
#include"Device.h"

//@brief	------  コマンドアロケーター制御クラス  ------
class CommandAllocator final 
{
public:
	CommandAllocator() = default;
	//デストラクタ
	~CommandAllocator();

	//@brief	---  コマンドアロケーター作成関数  ---
	//@return	コマンドアロケーターの作成可否
	[[nodiscard]] bool Create(const Device& Device, const D3D12_COMMAND_LIST_TYPE Type)noexcept;

	//@brief	---  コマンドアロケーターリセット関数  ---
	void Reset()noexcept;

	//@brief	---  コマンドアロケーター取得関数  ---
	//@return	コマンドアロケーターのポインター
	[[nodiscard]] ID3D12CommandAllocator* Get()const noexcept;

	//@brief	---  コマンドリストタイプ取得  ---
	//@return	コマンドリストタイプ
	[[nodiscard]] D3D12_COMMAND_LIST_TYPE GetType()const noexcept;
private:
	ID3D12CommandAllocator* Allocator_{};	//コマンドアロケーター
	D3D12_COMMAND_LIST_TYPE Type_{};		//コマンドリストタイプ
};
