//------  CommandList.cpp  ------
//------  参照  ------
#include"CommandList.h"
#include<cassert>

//デストラクタ
CommandList :: ~CommandList() {
	if (List_) {
		List_->Release();
		List_ = nullptr;
	}
}

//@brief	---  コマンドリスト作成関数  ---
//@return	コマンドリストの作成可否
[[nodiscard]] bool CommandList :: Create(const Device& Device, const CommandAllocator& Allocator)noexcept {
	
	//コマンドリスト作成
	const auto hr = Device.Get()->CreateCommandList(0, Allocator.GetType(), Allocator.Get(), nullptr, IID_PPV_ARGS(&List_));
	if (FAILED(hr)) {
		assert(false && "コマンドリスト作成失敗");
		return false;
	}
	//
	List_->Close();
	return true;
}

//@brief	---  コマンドリストリセット関数  ---
void CommandList :: Reset(const CommandAllocator& Allocator)noexcept {
	if (!List_) {
		assert(false && "コマンドリスト未作成");
	}
	//コマンドリストリセット
	List_->Reset(Allocator.Get(), nullptr);
}

//@brief	---  コマンドリスト取得関数  ---
//@return	コマンドリストのポインター
[[nodiscard]] ID3D12GraphicsCommandList* CommandList :: Get()const noexcept {
	if (!List_) {
		assert(false && "コマンドリスト未作成");
		return nullptr;
	}
	return List_;
}