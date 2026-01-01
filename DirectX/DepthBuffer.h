#pragma once
//------  DepthBuffer.h  ------
//------  参照  ------
#include"Device.h"
#include"../GameManager/DescriptorManager.h"
#include"../Window/Window.h"


//@brief	------  デプスバッファ制御クラス  ------
class DepthBuffer final
{
public:
	DepthBuffer() = default;
	~DepthBuffer() = default;

	//@brief	---  デプスバッファ作成関数  ---
	//@return	デプスバッファの作成可否
	[[nodiscard]] bool Create()noexcept;

	//@brief	---  デプスバッファ取得関数  ---
	//@return	デプスバッファのポインター
	[[nodiscard]] ID3D12Resource* Get()const noexcept;

	//@brief	---  ディスクリプタハンドル取得関数  ---
	//@return	ディスクリプタハンドル
	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE GetHandle()const noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12Resource> Buffer_{};		//デプスバッファ
	D3D12_CPU_DESCRIPTOR_HANDLE				Handle_{};		//ディスクリプタハンドル
};