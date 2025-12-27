#pragma once
//------  Triangle.h  ------
//------  参照  ------
#include"Polygon.h"

//@brief	------  三角形ポリゴン描画クラス  ------
class Troangle final:public Polygon
{
public:
	Troangle() = default;
	~Troangle() = default;

private:
	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] virtual bool CreateVertexBuffer()noexcept override;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] virtual bool CreateIndexBuffer()noexcept override;
};