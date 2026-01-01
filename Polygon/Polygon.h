#pragma once
//------  Polygon.h  ------
//------  参照  ------
#include"../DirectX/Device.h"
#include"../DirectX/CommandList.h"
#include<DirectXMath.h>

//@brief	------  ポリゴン描画制御基底クラス  ------
class Polygon
{
public:
	Polygon() = default;
	virtual ~Polygon() = default;

	//@brief	---  ポリゴン作成関数  ---
	[[nodiscard]] bool Create()noexcept;

	//@brief	---  描画指示関数  ---
	void Draw(const CommandList& List)noexcept;
protected:

	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] virtual bool CreateVertexBuffer()noexcept = 0;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] virtual bool CreateIndexBuffer()noexcept = 0;

protected://------  ポリゴン変数  ------

	Microsoft::WRL::ComPtr <ID3D12Resource> VertexBuffer_{};	//頂点バッファ
	Microsoft::WRL::ComPtr <ID3D12Resource> IndexBuffer_{};		//インデックスバッファ
	D3D12_VERTEX_BUFFER_VIEW	VertexView_{};		//頂点バッファビュー
	D3D12_INDEX_BUFFER_VIEW		IndexView_{};		//インデックスバッファビュー
	D3D_PRIMITIVE_TOPOLOGY		Topology_{};		//トポロジー(描画方法)
	UINT						IndexCount_{};		//インデックスカウント
};