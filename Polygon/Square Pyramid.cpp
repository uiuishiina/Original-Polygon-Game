//------  Square Pyramid.cpp  ------
//------  参照  ------
#include"Square Pyramid.h"
#include<cassert>


//@brief	---  描画指示関数  ---
void SquarePyramid :: Draw(const CommandList& List)noexcept {
	// 頂点バッファの設定
	List.Get()->IASetVertexBuffers(0, 1, &VertexView_[0]);
	// インデックスバッファの設定
	List.Get()->IASetIndexBuffer(&IndexView_);
	// プリミティブ形状の設定
	List.Get()->IASetPrimitiveTopology(Topology_);
	// 描画コマンド
	List.Get()->DrawIndexedInstanced(IndexCount_, 1, 0, 0, 0);

	// 頂点バッファの設定
	List.Get()->IASetVertexBuffers(0, 1, &VertexView_[1]);
	// インデックスバッファの設定
	List.Get()->IASetIndexBuffer(&IndexView_);
	// プリミティブ形状の設定
	List.Get()->IASetPrimitiveTopology(Topology_);
	// 描画コマンド
	List.Get()->DrawIndexedInstanced(IndexCount_, 1, 0, 0, 0);

	// 頂点バッファの設定
	List.Get()->IASetVertexBuffers(0, 1, &VertexView_[2]);
	// 描画コマンド
	List.Get()->DrawIndexedInstanced(IndexCount_, 1, 0, 0, 0);

	// 頂点バッファの設定
	List.Get()->IASetVertexBuffers(0, 1, &VertexView_[3]);
	// 描画コマンド
	List.Get()->DrawIndexedInstanced(IndexCount_, 1, 0, 0, 0);
}

//@brief	---  頂点バッファ作成関数  ---
[[nodiscard]] bool SquarePyramid :: CreateVertexBuffer()noexcept {

	// トポロジーの設定（三角形）
	Topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	//頂点データ
	if (!CreateView(0)) {
		assert(false && "失敗０");
		return false;
	}
	
	if (!CreateView(1)) {
		assert(false && "失敗1");
		return false;
	}
	
	if (!CreateView(2)) {
		assert(false && "失敗2");
		return false;
	}

	if (!CreateView(3)) {
		assert(false && "失敗2");
		return false;
	}

	return true;
}

//@brief	---  頂点バッファビュー作成関数  ---
//@param	vertex	-- 頂点データ --
//@param	Buffer_	-- 頂点バッファ --
//@param	map	-- マップ --
//@param	num	-- 番号 --
[[nodiscard]] bool SquarePyramid :: CreateView(int num)noexcept {

	Vertex* UseV{};
	switch (num)
	{
	case 0:
		UseV = V0;
		break;
	case 1:
		UseV = V1;
		break;
	case 2:
		UseV = V2;
		break;
	case 3:
		UseV = V3;
		break;
	default:
		return false;
	}
	//頂点データサイズ
	const auto VertexSize = sizeof(Vertex[3]);
	//ヒープ設定
	D3D12_HEAP_PROPERTIES heap{};
	heap.Type = D3D12_HEAP_TYPE_UPLOAD;
	heap.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap.CreationNodeMask = 1;
	heap.VisibleNodeMask = 1;

	//リソース設定
	D3D12_RESOURCE_DESC Desc{};
	Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	Desc.Alignment = 0;
	Desc.Width = VertexSize;
	Desc.Height = 1;
	Desc.DepthOrArraySize = 1;
	Desc.MipLevels = 1;
	Desc.Format = DXGI_FORMAT_UNKNOWN;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	//頂点バッファ生成
	auto hr = Device::Instance().Get()->CreateCommittedResource(
		&heap,
		D3D12_HEAP_FLAG_NONE,
		&Desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&VertexBuffer_[num])
	);
	if (FAILED(hr)) {
		assert(false && "頂点バッファ作成失敗");
		return false;
	}

	//バッファをマップ
	Vertex* data{};
	hr = VertexBuffer_[num]->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(hr)) {
		assert(false && "頂点バッファマップ失敗");
		return false;
	}

	//データをコピー
	memcpy_s(data, VertexSize, UseV, VertexSize);
	//マップ解除
	VertexBuffer_[num]->Unmap(0, nullptr);

	//頂点バッファビューの設定
	VertexView_[num].BufferLocation = VertexBuffer_[num]->GetGPUVirtualAddress();
	VertexView_[num].SizeInBytes = VertexSize;
	VertexView_[num].StrideInBytes = sizeof(Vertex);

	return true;
}

//@brief	---  インデックスバッファ作成関数  ---
[[nodiscard]] bool SquarePyramid :: CreateIndexBuffer()noexcept {

	//頂点インデックスデータ
	uint16_t Index_[] = { 0,1,2 };
	//頂点インデックスデータサイズ
	const auto Indexsize = sizeof(Index_);

	D3D12_HEAP_PROPERTIES heap{};
	heap.Type = D3D12_HEAP_TYPE_UPLOAD;
	heap.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heap.CreationNodeMask = 1;
	heap.VisibleNodeMask = 1;

	//リソース設定
	D3D12_RESOURCE_DESC Desc{};
	Desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	Desc.Alignment = 0;
	Desc.Width = Indexsize;
	Desc.Height = 1;
	Desc.DepthOrArraySize = 1;
	Desc.MipLevels = 1;
	Desc.Format = DXGI_FORMAT_UNKNOWN;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	Desc.Flags = D3D12_RESOURCE_FLAG_NONE;

	//インデックスバッファ作成
	auto hr = Device::Instance().Get()->CreateCommittedResource(
		&heap,
		D3D12_HEAP_FLAG_NONE,
		&Desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&IndexBuffer_)
	);
	if (FAILED(hr)) {
		assert(false && "インデックスバッファ作成失敗");
		return false;
	}

	//バッファをマップ
	uint16_t* data{};
	hr = IndexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(hr)) {
		assert(false && "頂点バッファマップ失敗");
		return false;
	}
	//データをコピー
	memcpy_s(data, Indexsize, Index_, Indexsize);
	//マップ解除
	IndexBuffer_->Unmap(0, nullptr);

	//頂点バッファビューの設定
	IndexView_.BufferLocation = IndexBuffer_->GetGPUVirtualAddress();
	IndexView_.SizeInBytes = Indexsize;
	IndexView_.Format = DXGI_FORMAT_R16_UINT;

	//インデックスカウント設定
	IndexCount_ = _countof(Index_);

	return true;
}