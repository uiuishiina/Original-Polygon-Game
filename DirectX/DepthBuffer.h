#pragma once
//------  DepthBuffer.h  ------
//------  参照  ------
#include"Device.h"
#include"Descriptor_Heap.h"
#include"../Window/Window.h"


//@brief	------  デプスバッファ制御クラス  ------
class DepthBuffer final
{
public:
	DepthBuffer() = default;
	~DepthBuffer() = default;

	//@brief	---  デプスバッファ作成関数  ---
	//@return	デプスバッファの作成可否
	[[nodiscard]] bool Create(const DescriptorHeap& heap, const Window& window)noexcept;


private:
};