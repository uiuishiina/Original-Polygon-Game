//------  CommandAllocator.cpp  ------
//------  参照  ------
#include"CommandAllocator.h"
#include<cassert>


//@brief	---  コマンドアロケーター作成関数  ---
//@return	コマンドアロケーターの作成可否
[[nodiscard]] bool CommandAllocator :: Create(const D3D12_COMMAND_LIST_TYPE Type)noexcept {

	Type_ = Type;
	//コマンドアロケーター作成
	const auto hr = Device::Instance().Get()->CreateCommandAllocator(Type_, IID_PPV_ARGS(&Allocator_));
	if (FAILED(hr)) {
		assert(false && "コマンドアロケーター作成失敗");
		return false;
	}
	return true;
}

//@brief	---  コマンドアロケーターリセット関数  ---
void CommandAllocator :: Reset()noexcept {
	assert(Allocator_ && "コマンドアロケーター未作成");
	Allocator_->Reset();
}

//@brief	---  コマンドアロケーター取得関数  ---
//@return	コマンドアロケーターのポインター
[[nodiscard]] ID3D12CommandAllocator* CommandAllocator :: Get()const noexcept {
	assert(Allocator_ && "コマンドアロケーター未作成");
	return Allocator_.Get();
}

//@brief	---  コマンドリストタイプ取得  ---
//@return	コマンドリストタイプ
[[nodiscard]] D3D12_COMMAND_LIST_TYPE CommandAllocator :: GetType()const noexcept {
	assert(Allocator_ && "コマンドアロケーター未作成");
	return Type_;
}