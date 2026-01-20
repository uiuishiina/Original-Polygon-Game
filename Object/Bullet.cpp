//------  Bullet.cpp  ------
//------  参照  ------
#include"Bullet.h"
float movedle = 0.0f;

void Bullet::Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<Square>();//Square//Triangle
	DirectX::XMFLOAT3 parentPos{};
	if (auto parent = MyGame::GameObjectManager::Instance().GetGameObject(Parent_)) {
		DirectX::XMStoreFloat3(&parentPos, parent.value()->GetWorld().r[3]);
	}
	SetData(parentPos, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.5f }, PolygonID_);
}

void Bullet::UpDate()noexcept {
	constexpr float moveSpeed = 0.3f;
	DirectX::XMFLOAT3 pos{};
	pos.z += moveSpeed;
	movedle += moveSpeed;
	// ワールド行列の更新
	World_ = DirectX::XMMatrixMultiply(World_, DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));
	GameObject::UpDate();
	MyGame::GameObjectManager::Instance().SetHit(GetMyHandle());
}

//@brief	---  描画指示設定  ---
void Bullet::SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	GameObject::SetDrawCommand(List, slot);
	PolygonManager::Instance().Draw(List, PolygonID_);
}

//@brief	---  衝突相手取得関数  ---
[[nodiscard]] UINT64 Bullet :: HitClassHandle()noexcept {
	return ID::Get<Enemy>();
}

//@brief	---  衝突時処理関数  ---
void Bullet :: OnHit()noexcept {
	MyGame::GameObjectManager::Instance().DeleteGameObject(GetMyHandle());
}