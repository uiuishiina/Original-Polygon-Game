#pragma once
//------  Square Pyramid.h  ------
//------  参照  ------
#include"Polygon.h"


//@brief	------  四角錐ポリゴン制御関数  ------
class SquarePyramid final :public Polygon
{
public:
	SquarePyramid() = default;
	~SquarePyramid() = default;


	//@brief	---  描画指示関数  ---
	virtual void Draw(const CommandList& List)noexcept override;
private:
	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] virtual bool CreateVertexBuffer()noexcept override;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] virtual bool CreateIndexBuffer()noexcept override;

	//@brief	---  頂点バッファビュー作成関数  ---
	[[nodiscard]] bool CreateView(int num)noexcept;

	Microsoft::WRL::ComPtr <ID3D12Resource> VertexBuffer_[4]{};	//頂点バッファ
	D3D12_VERTEX_BUFFER_VIEW	VertexView_[4]{};			//頂点バッファビュー

	Vertex V0[3] = {
		//頂点位置					//頂点色
		{{	0.0f,	0.5f,	0.0f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	0.5f,	-0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	-0.5f,	-0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},
	};
	Vertex V1[3] = {
		//頂点位置					//頂点色
		{{	0.0f,	0.5f,	0.0f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	-0.5f,	-0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	-0.5f,	-0.5f,	0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},
	};
	Vertex V2[3] = {
		//頂点位置					//頂点色
		{{	0.0f,	0.5f,	0.0f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	-0.5f,	-0.5f,	0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	0.5f,	-0.5f,	0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},
	};
	Vertex V3[3] = {
		//頂点位置					//頂点色
		{{	0.0f,	0.5f,	0.0f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	0.5f,	-0.5f,	0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},
		{{	0.5f,	-0.5f,	-0.5f},{	1.0f,	1.0f,	1.0f,	1.0f}},
	};
};