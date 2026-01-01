#pragma once
//------  Triangle.h  ------
//------  参照  ------
#include"Polygon.h"

//@brief	------  三角形ポリゴン描画クラス  ------
class Triangle final:public Polygon
{
public:
	Triangle() = default;
	~Triangle() = default;

private:
	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] virtual bool CreateVertexBuffer()noexcept override;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] virtual bool CreateIndexBuffer()noexcept override;
};