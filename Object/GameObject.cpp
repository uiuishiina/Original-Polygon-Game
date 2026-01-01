//------  GameObject.cpp  ------
//------  参照  ------
#include"GameObject.h"


//@brief	---  初期化関数  ---
void GameObject :: Initialize()noexcept {
	CreateConstantBuffer();
}
//@brief	---  描画指示設定  ---
void GameObject :: SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	// コンスタントバッファの設定
	List.Get()->SetGraphicsRootDescriptorTable(
		slot,
		MyBuffer_.GetHandle());
}

//@brief	---  UpDate()関数  ---
void GameObject :: UpDate()noexcept {
	UpDateConstantBuffer(BufferData{ DirectX::XMMatrixTranspose(World_), Color_ });
}
//@brief	---  オブジェクトデータ設定関数  ---
	//@param	ポジション
	//@param	回転
	//@param	スケール
	//@param	カラー
	//@param	ポリゴン識別子
void GameObject :: SetData(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rotate, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT4 color, UINT64 ID)noexcept {
	// ワールド行列の計算
	DirectX::XMMATRIX matScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	DirectX::XMMATRIX rotation = DirectX::XMMatrixRotationRollPitchYaw(rotate.x, rotate.y, rotate.z);
	DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	World_ = matScale * rotation * translation;

	// カラーの設定
	Color_ = color;
	// 形状識別子の設定
	PolygonID_ = ID;

	// 衝突判定用の半径を設定
	Radius_ = (scale.x + scale.y + scale.z) / (3.0f * 2.0f);
}

//@brief	---  コンスタントバッファ作成関数  ---
//@return	コンスタントバッファの作成可否
[[nodiscard]] bool GameObject :: CreateConstantBuffer()noexcept {
	//コンスタントバッファ作成
	if (!MyBuffer_.Create(sizeof(BufferData))) {
		assert(false && "コンスタントバッファ作成失敗");
		return false;
	}
	return true;
}

//@brief	---  コンスタントバッファ更新関数  ---
template <class T>
void GameObject :: UpDateConstantBuffer(const T& data)noexcept {
	std::byte* dst{};
	MyBuffer_.Get()->Map(0, nullptr, reinterpret_cast<void**>(&dst));
	memcpy_s(dst, sizeof(T), &data, sizeof(T));
	MyBuffer_.Get()->Unmap(0, nullptr);
}

//@brief	---  クラス識別子設定関数  ---
void GameObject :: SetClassID(UINT64 ID)noexcept {
	ClassID_ = ID;
}

//@brief	---  個別識別子設定関数  ---
void GameObject :: SetMyHandle(UINT64 ID)noexcept {
	MyHandle_ = ID;
}

//@brief	---  ワールド行列取得関数  ---
//@return	World_
[[nodiscard]] DirectX::XMMATRIX GameObject :: GetWorld()const noexcept {
	return World_;
}

//@brief	---  カラー取得関数  ---
//@return	Color_
[[nodiscard]] DirectX::XMFLOAT4 GameObject :: GetColor()const noexcept {
	return Color_;
}

//@brief	---  クラス識別子取得関数  ---
//@return	クラス識別子
[[nodiscard]] UINT64 GameObject :: GetClassID()const noexcept {
	return ClassID_;
}

//@brief	---  個別識別子取得関数  ---
//@return	個別識別子
[[nodiscard]] UINT64 GameObject :: GetMyHandle()const noexcept {
	return MyHandle_;
}

//@brief	---  あたり範囲取得関数  ---
//@return	あたり範囲
[[nodiscard]] float GameObject :: GetRadius()const noexcept {
	return Radius_;
}