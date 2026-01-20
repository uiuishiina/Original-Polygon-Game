//------  Triangle.cpp  ------
//------  参照  ------
#include"Triangle.h"
#include<cassert>

//@brief	---  頂点バッファ作成関数  ---
[[nodiscard]] bool Triangle:: CreateVertexBuffer()noexcept {

	//頂点データ
	Vertex Vertex_[] = {
		//頂点位置					//頂点色
		{{	0.0f,	0.5f,	0.0f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	0.5f,	-0.5f,	0.0f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	-0.5f,	-0.5f,	0.0f},{	1.0f,	1.0f,	1.0f,	1.0f}},
	};

	//頂点データサイズ
	const auto VertexSize = sizeof(Vertex_);

	//ヒープ設定
	D3D12_HEAP_PROPERTIES heap{};
	heap.Type					= D3D12_HEAP_TYPE_UPLOAD;
	heap.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
	heap.CreationNodeMask		= 1;
	heap.VisibleNodeMask		= 1;

	//リソース設定
	D3D12_RESOURCE_DESC Desc{};
	Desc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
	Desc.Alignment			= 0;
	Desc.Width				= VertexSize;
	Desc.Height				= 1;
	Desc.DepthOrArraySize	= 1;
	Desc.MipLevels			= 1;
	Desc.Format				= DXGI_FORMAT_UNKNOWN;
	Desc.SampleDesc.Count	= 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	Desc.Flags				= D3D12_RESOURCE_FLAG_NONE;

	//頂点バッファ生成
	auto hr = Device::Instance().Get()->CreateCommittedResource(
		&heap,
		D3D12_HEAP_FLAG_NONE,
		&Desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&VertexBuffer_)
	);
	if (FAILED(hr)) {
		assert(false && "頂点バッファ作成失敗");
		return false;
	}

	//バッファをマップ
	Vertex* data{};
	hr = VertexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&data));
	if (FAILED(hr)) {
		assert(false && "頂点バッファマップ失敗");
		return false;
	}
	//データをコピー
	memcpy_s(data, VertexSize, Vertex_, VertexSize);
	//マップ解除
	VertexBuffer_->Unmap(0, nullptr);

	//頂点バッファビューの設定
	VertexView_.BufferLocation	= VertexBuffer_->GetGPUVirtualAddress();
	VertexView_.SizeInBytes		= VertexSize;
	VertexView_.StrideInBytes	= sizeof(Vertex);

	// トポロジーの設定（三角形）
	Topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	return true;
}

//@brief	---  インデックスバッファ作成関数  ---
[[nodiscard]] bool Triangle:: CreateIndexBuffer()noexcept {

	//頂点インデックスデータ
	uint16_t Index_[] = { 0,1,2 };
	//頂点インデックスデータサイズ
	const auto Indexsize = sizeof(Index_);

	D3D12_HEAP_PROPERTIES heap{};
	heap.Type					= D3D12_HEAP_TYPE_UPLOAD;
	heap.CPUPageProperty		= D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heap.MemoryPoolPreference	= D3D12_MEMORY_POOL_UNKNOWN;
	heap.CreationNodeMask		= 1;
	heap.VisibleNodeMask		= 1;

	//リソース設定
	D3D12_RESOURCE_DESC Desc{};
	Desc.Dimension			= D3D12_RESOURCE_DIMENSION_BUFFER;
	Desc.Alignment			= 0;
	Desc.Width				= Indexsize;
	Desc.Height				= 1;
	Desc.DepthOrArraySize	= 1;
	Desc.MipLevels			= 1;
	Desc.Format				= DXGI_FORMAT_UNKNOWN;
	Desc.SampleDesc.Count	= 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Layout				= D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	Desc.Flags				= D3D12_RESOURCE_FLAG_NONE;

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
	IndexView_.BufferLocation	= IndexBuffer_->GetGPUVirtualAddress();
	IndexView_.SizeInBytes		= Indexsize;
	IndexView_.Format			= DXGI_FORMAT_R16_UINT;

	//インデックスカウント設定
	IndexCount_ = _countof(Index_);

	return true;
}