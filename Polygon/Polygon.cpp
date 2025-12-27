//------  Polygon.cpp  ------
//------  参照  ------
#include"Polygon.h"
#include<cassert>


//@brief	---  ポリゴン作成関数  ---
[[nodiscard]] bool Polygon :: Create()noexcept {

	//頂点バッファ作成
	if (!CreateVertexBuffer()) {
		assert(false && "頂点バッファ作成失敗(Create)");
		return false;
	}
	//インデックスバッファ作成
	if (!CreateIndexBuffer()) {
		assert(false && "インデックスバッファ作成失敗(Create)");
		return false;
	}
	return true;
}

//@brief	---  描画指示関数  ---
void Polygon :: Draw(const CommandList& List)noexcept {

	// 頂点バッファの設定
	List.Get()->IASetVertexBuffers(0, 1, &VertexView_);
	// インデックスバッファの設定
	List.Get()->IASetIndexBuffer(&IndexView_);
	// プリミティブ形状の設定
	List.Get()->IASetPrimitiveTopology(Topology_);
	// 描画コマンド
	List.Get()->DrawIndexedInstanced(IndexCount_, 1, 0, 0, 0);

}