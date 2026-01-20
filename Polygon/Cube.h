#pragma once
//------  Cube.h  ------
//------  参照  ------
#include"Polygon.h"

//@brief	------  立方体ポリゴン描画クラス  ------
class Cube final:public Polygon
{
public:
	Cube() = default;
	~Cube() = default;

private:
	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] bool CreateVertexBuffer()noexcept override;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] bool CreateIndexBuffer()noexcept override;
};