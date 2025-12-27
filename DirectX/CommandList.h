#pragma once
//------  CommandList.h  ------
//------  参照  ------
#include"Device.h"
#include"CommandAllocator.h"

//@brief	------  コマンドリスト制御クラス  ------
class CommandList final
{
public:
	CommandList() = default;
	~CommandList() = default;

	//@brief	---  コマンドリスト作成関数  ---
	//@return	コマンドリストの作成可否
	[[nodiscard]] bool Create(const CommandAllocator& Allocator)noexcept;

	//@brief	---  コマンドリストリセット関数  ---
	void Reset(const CommandAllocator& Allocator)noexcept;

	//@brief	---  コマンドリスト取得関数  ---
	//@return	コマンドリストのポインター
	[[nodiscard]] ID3D12GraphicsCommandList* Get()const noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12GraphicsCommandList> List_{};	//コマンドリスト
};
