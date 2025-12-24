//------  CommandAllocator.cpp  ------
//------  参照  ------
#include"CommandAllocator.h"
#include<cassert>

//デストラクタ
CommandAllocator :: ~CommandAllocator() {
	if (Allocator_) {
		Allocator_->Release();
		Allocator_ = nullptr;
	}
}

//@brief	---  コマンドアロケーター作成関数  ---
//@return	コマンドアロケーターの作成可否
[[nodiscard]] bool CommandAllocator :: Create(const Device& Device, const D3D12_COMMAND_LIST_TYPE Type)noexcept {

	Type_ = Type;
	//コマンドアロケーター作成
	const auto hr = Device.Get()->CreateCommandAllocator(Type_, IID_PPV_ARGS(&Allocator_));
	if (FAILED(hr)) {
		assert(false && "コマンドアロケーター作成失敗");
		return false;
	}
	return true;
}

//@brief	---  コマンドアロケーターリセット関数  ---
void CommandAllocator :: Reset()noexcept {
	if (!Allocator_) {
		assert(false && "コマンドアロケーター未作成");
	}
	Allocator_->Reset();
}

//@brief	---  コマンドアロケーター取得関数  ---
//@return	コマンドアロケーターのポインター
[[nodiscard]] ID3D12CommandAllocator* CommandAllocator :: Get()const noexcept {
	if (!Allocator_) {
		assert(false && "コマンドアロケーター未作成");
		return nullptr;
	}
	return Allocator_;
}

//@brief	---  コマンドリストタイプ取得  ---
//@return	コマンドリストタイプ
[[nodiscard]] D3D12_COMMAND_LIST_TYPE CommandAllocator :: GetType()const noexcept {
	if (!Allocator_) {
		assert(false && "コマンドアロケーター未作成");
	}
	return Type_;
}