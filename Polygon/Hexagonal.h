#pragma once
//------  Hexagonal.h  ------
//------  参照  ------
#include"Polygon.h"

//@brief	------  六角形ポリゴン描画クラス  ------
class Hexagonal final :public Polygon
{
public:
	Hexagonal() = default;
	~Hexagonal() = default;

private:
	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] virtual bool CreateVertexBuffer()noexcept override;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] virtual bool CreateIndexBuffer()noexcept override;
};