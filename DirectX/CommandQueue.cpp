//------  CommandQueue.cpp  ------
//------  参照  ------
#include"CommandQueue.h"
#include<cassert>

//@brief	---  コマンドキュー作成関数  ---
//@return	コマンドキュー作成の成否
[[nodiscard]] bool CommandQueue :: Create()noexcept {

	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type		= D3D12_COMMAND_LIST_TYPE_DIRECT;
	desc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Flags		= D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.NodeMask	= 0;

	//コマンドキューの作成
	const auto hr = Device::Instance().Get()->CreateCommandQueue(&desc, IID_PPV_ARGS(&CommandQueue_));
	if (FAILED(hr)) {
		assert(false && "コマンドキュー作成失敗");
		return false;
	}
	return true;
}

//@brief	---  コマンドキュー取得関数  ---
//@return	コマンドキューのポインター
[[nodiscard]] ID3D12CommandQueue* CommandQueue :: Get()const noexcept {
	if (!CommandQueue_) {
		assert(false && "コマンドキュー未作成");
		return nullptr;
	}
	return CommandQueue_.Get();
}