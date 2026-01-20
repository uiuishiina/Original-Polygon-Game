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
private:
	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] bool CreateVertexBuffer()noexcept override;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] bool CreateIndexBuffer()noexcept override;
};