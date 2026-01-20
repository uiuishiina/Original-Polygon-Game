//------  Cube.cpp  ------
//------  参照  ------
#include"OutLineCube.h"
#include<cassert>

//@brief	---  描画指示関数  ---
void OutLineCube :: Draw(const CommandList& List)noexcept {
	// 頂点バッファの設定
	List.Get()->IASetVertexBuffers(0, 1, &VertexView_);
	// インデックスバッファの設定
	List.Get()->IASetIndexBuffer(&IndexView_);
	// プリミティブ形状の設定
	List.Get()->IASetPrimitiveTopology(Topology_);
	// 描画コマンド
	List.Get()->DrawIndexedInstanced(IndexCount_, 1, 0, 0, 0);



	// 頂点バッファの設定
	List.Get()->IASetVertexBuffers(0, 1, &OutlineVertexView_);
	// インデックスバッファの設定
	List.Get()->IASetIndexBuffer(&OutlineIndexView_);
	// プリミティブ形状の設定
	List.Get()->IASetPrimitiveTopology(Topology_);
	// 描画コマンド
	List.Get()->DrawIndexedInstanced(OutlineIndexCount_, 1, 0, 0, 0);
}

//@brief	---  頂点バッファ作成関数  ---
[[nodiscard]] bool OutLineCube :: CreateVertexBuffer()noexcept {
	
	//ポリゴン作成
	{
		Vertex V[] = {
			//-----  正面  -----
			//頂点位置					//頂点色
			{{	-0.4f,	 0.4f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			{{	 0.4f,	 0.4f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			{{	-0.4f,	-0.4f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			{{	 0.4f,	-0.4f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  左面  -----
			//頂点位置					//頂点色
			{{	-0.5f,	 0.4f,	 0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			{{	-0.5f,	 0.4f,	-0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			{{	-0.5f,	-0.4f,	 0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			{{	-0.5f,	-0.4f,	-0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  背面  -----
			//頂点位置					//頂点色
			{{	 0.4f,	 0.4f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			{{	-0.4f,	 0.4f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			{{	 0.4f,	-0.4f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			{{	-0.4f,	-0.4f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  右面  -----
			//頂点位置					//頂点色
			{{	 0.5f,	 0.4f,	-0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			{{	 0.5f,	 0.4f,	 0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			{{	 0.5f,	-0.4f,	-0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			{{	 0.5f,	-0.4f,	 0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  上面  -----
			//頂点位置					//頂点色
			{{	-0.4f,	 0.5f,	 0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			{{	 0.4f,	 0.5f,	 0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			{{	-0.4f,	 0.5f,	-0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			{{	 0.4f,	 0.5f,	-0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  下面  -----
			//頂点位置					//頂点色
			{{	 0.4f,	-0.5f,	 0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			{{	-0.4f,	-0.5f,	 0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			{{	 0.4f,	-0.5f,	-0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			{{	-0.4f,	-0.5f,	-0.4f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---
		};

		//頂点データサイズ
		const auto VertexSize = sizeof(V);

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
		memcpy_s(data, VertexSize, V, VertexSize);
		//マップ解除
		VertexBuffer_->Unmap(0, nullptr);

		//頂点バッファビューの設定
		VertexView_.BufferLocation = VertexBuffer_->GetGPUVirtualAddress();
		VertexView_.SizeInBytes = VertexSize;
		VertexView_.StrideInBytes = sizeof(Vertex);
	}

	//アウトライン作成

	{
		Vertex V[] = {
			//-----  正面  -----
			//頂点位置					//頂点色
			{{	-0.49f,	 0.49f,	-0.49f},{	0.0f,	1.0f,	0.0f,	1.0f}},	//---  左上  ---
			{{	 0.49f,	 0.49f,	-0.49f},{	0.0f,	1.0f,	0.0f,	1.0f}},	//---  右上  ---
			{{	-0.49f,	-0.49f,	-0.49f},{	0.0f,	1.0f,	0.0f,	1.0f}},	//---  左下  ---
			{{	 0.49f,	-0.49f,	-0.49f},{	0.0f,	1.0f,	0.0f,	1.0f}},	//---  右下  ---

			//-----  左面  -----
			//頂点位置					//頂点色
			{{	-0.49f,	 0.49f,	 0.49f},{	1.0f,	1.0f,	0.0f,	1.0f}},	//---  左上  ---
			//{{	-0.5f,	 0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			{{	-0.49f,	-0.49f,	 0.49f},{	1.0f,	1.0f,	0.0f,	1.0f}},	//---  左下  ---
			//{{	-0.5f,	-0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  背面  -----
			//頂点位置					//頂点色
			{{	 0.49f,	 0.49f,	 0.49f},{	0.0f,	1.0f,	0.0f,	1.0f}},	//---  左上  ---
			//{{	-0.5f,	 0.5f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			{{	 0.49f,	-0.49f,	 0.49f},{	0.0f,	1.0f,	0.0f,	1.0f}},	//---  左下  ---
			//{{	-0.5f,	-0.5f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  右面  -----
			//頂点位置					//頂点色
			//{{	 0.5f,	 0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			//{{	 0.5f,	 0.5f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			//{{	 0.5f,	-0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			//{{	 0.5f,	-0.5f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  上面  -----
			//頂点位置					//頂点色
			//{{	-0.5f,	 0.5f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			//{{	 0.5f,	 0.5f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			//{{	-0.5f,	 0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			//{{	 0.5f,	 0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---

			//-----  下面  -----
			//頂点位置					//頂点色
			//{{	 0.5f,	-0.5f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左上  ---
			//{{	-0.5f,	-0.5f,	 0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右上  ---
			//{{	 0.5f,	-0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  左下  ---
			//{{	-0.5f,	-0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},	//---  右下  ---
		};

		//頂点データサイズ
		const auto VertexSize = sizeof(V);

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
			IID_PPV_ARGS(&OutlineVertexBuffer_)
		);
		if (FAILED(hr)) {
			assert(false && "頂点バッファ作成失敗");
			return false;
		}

		//バッファをマップ
		Vertex* data{};
		hr = OutlineVertexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&data));
		if (FAILED(hr)) {
			assert(false && "頂点バッファマップ失敗");
			return false;
		}
		//データをコピー
		memcpy_s(data, VertexSize, V, VertexSize);
		//マップ解除
		OutlineVertexBuffer_->Unmap(0, nullptr);

		//頂点バッファビューの設定
		OutlineVertexView_.BufferLocation = OutlineVertexBuffer_->GetGPUVirtualAddress();
		OutlineVertexView_.SizeInBytes = VertexSize;
		OutlineVertexView_.StrideInBytes = sizeof(Vertex);
	}
	// トポロジーの設定（三角形）
	Topology_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	return true;
}

//@brief	---  インデックスバッファ作成関数  ---
[[nodiscard]] bool OutLineCube :: CreateIndexBuffer()noexcept {

	//ポリゴンIndex_作成
	{
		//頂点インデックスデータ
		uint16_t Index_[] = {
			0,1,2,1,3,2,		//-----  正面  -----
			4,5,6,5,7,6,		//-----  左面  -----
			8,9,10,9,11,10,		//-----  背面  -----
			12,13,14,13,15,14,	//-----  右面  -----
			16,17,18,17,19,18,	//-----  上面  -----
			20,21,22,21,23,22	//-----  下面  -----
		};
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
	}

	//アウトラインIndex_作成
	{
		//頂点インデックスデータ
		uint16_t Index_[] = {
			0,1,2,1,3,2,		//-----  正面  -----
			4,0,5,0,2,5,		//-----  左面  -----
			6,4,7,4,5,7,		//-----  背面  -----
			1,6,3,6,7,3,		//-----  右面  -----
			4,6,0,6,1,0,		//-----  上面  -----
			7,5,3,5,2,3			//-----  下面  -----
		};
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
			IID_PPV_ARGS(&OutlineIndexBuffer_)
		);
		if (FAILED(hr)) {
			assert(false && "インデックスバッファ作成失敗");
			return false;
		}

		//バッファをマップ
		uint16_t* data{};
		hr = OutlineIndexBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&data));
		if (FAILED(hr)) {
			assert(false && "頂点バッファマップ失敗");
			return false;
		}
		//データをコピー
		memcpy_s(data, Indexsize, Index_, Indexsize);
		//マップ解除
		OutlineIndexBuffer_->Unmap(0, nullptr);

		//頂点バッファビューの設定
		OutlineIndexView_.BufferLocation = OutlineIndexBuffer_->GetGPUVirtualAddress();
		OutlineIndexView_.SizeInBytes = Indexsize;
		OutlineIndexView_.Format = DXGI_FORMAT_R16_UINT;

		//インデックスカウント設定
		OutlineIndexCount_ = _countof(Index_);
	}
	return true;
}