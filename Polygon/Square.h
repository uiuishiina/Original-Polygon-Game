#pragma once
//------  Square.h  ------
//------  参照  ------
#include"Polygon.h"

//@brief	------  四角形ポリゴン描画クラス  ------
class Square final :public Polygon
{
public:
	Square() = default;
	~Square() = default;

private:
	//@brief	---  頂点バッファ作成関数  ---
	[[nodiscard]] virtual bool CreateVertexBuffer()noexcept override;

	//@brief	---  インデックスバッファ作成関数  ---
	[[nodiscard]] virtual bool CreateIndexBuffer()noexcept override;
};