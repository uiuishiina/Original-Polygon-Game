//------  Fence.cpp  ------
//------  参照  ------
#include"Fence.h"
#include<cassert>


//@brief	---  フェンス作成関数  ---
//@return	フェンスの作成可否
[[nodiscard]] bool Fence :: Create()noexcept {

	//フェンスの作成
	const auto hr = Device::Instance().Get()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Fence_));
	if (FAILED(hr)) {
		assert(false && "フェンス作成失敗");
		return false;
	}
	//同期用イベントハンドル作成
	WaitGPUEvent_ = CreateEvent(nullptr, false, false, "WAIT_GPU");
	if (!WaitGPUEvent_) {
		assert(false && "イベントハンドル作成失敗");
		return false;
	}
	return true;
}

//@brief	---  同期待機関数  ---
void Fence :: Wait(UINT64 Value)const noexcept {
	if (!Fence_) {
		assert(false && "フェンス未作成");
		return;
	}
	//待機処理
	if (Fence_->GetCompletedValue() < Value) {
		//イベントが終了するまで待機
		Fence_->SetEventOnCompletion(Value, WaitGPUEvent_);
		//イベント設定
		WaitForSingleObject(WaitGPUEvent_, INFINITE);
	}
}

//@brief	---  フェンス取得関数  ---
[[nodiscard]] ID3D12Fence* Fence :: Get()const noexcept {
	assert(Fence_ && "フェンス未作成");
	return Fence_.Get();
}