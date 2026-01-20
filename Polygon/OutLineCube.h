#pragma once
//------  OutLineCube.h  ------
//------  参照  ------
#include"Polygon.h"

//@brief	------  アウトライン付き立方体ポリゴン描画クラス  ------
class OutLineCube final :public Polygon
{
public:
	OutLineCube() = default;
	~OutLineCube() = default;

	//@brief	---  描画指示関数  ---
	void Draw(const CommandList& List)noexcept override;

private:
	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] bool CreateVertexBuffer()noexcept override;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] bool CreateIndexBuffer()noexcept override;

	Microsoft::WRL::ComPtr <ID3D12Resource> OutlineVertexBuffer_{};	//アウトライン頂点バッファ
	Microsoft::WRL::ComPtr <ID3D12Resource> OutlineIndexBuffer_{};	//アウトラインインデックスバッファ
	D3D12_VERTEX_BUFFER_VIEW	OutlineVertexView_{};				//アウトライン頂点バッファビュー
	D3D12_INDEX_BUFFER_VIEW		OutlineIndexView_{};				//アウトラインインデックスバッファビュー
	UINT						OutlineIndexCount_{};				//アウトラインインデックスカウント
};