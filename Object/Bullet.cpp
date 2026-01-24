//------  Bullet.cpp  ------
//------  参照  ------
#include"Bullet.h"
float movedle = 0.0f;
float Brat = 0;

void Bullet::Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<Square>();//Square//Triangle//Cube
	DirectX::XMFLOAT3 parentPos{};
	movedle = 0.0f;
	if (auto parent = MyGame::GameObjectManager::Instance().GetGameObject(Parent_)) {
		DirectX::XMStoreFloat3(&parentPos, parent.value()->GetWorld().r[3]);
	}
	SetData(parentPos, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 0.5f }, PolygonID_);
}

void Bullet::UpDate()noexcept {
	constexpr float moveSpeed = 0.3f;
	
	//------  ポジション取得  ------
	DirectX::XMFLOAT4X4 f4x4 = {};
	DirectX::XMStoreFloat4x4(&f4x4, World_);//DirectX::XMMatrixIdentity()

	//------  移動  ------
	f4x4._43 += moveSpeed;
	movedle += moveSpeed;

	World_ = DirectX::XMMatrixMultiply(World_, DirectX::XMMatrixTranslation(f4x4._41, f4x4._42, f4x4._43));

	//--------------------

	//------  回転  ------
	Brat += 0.5f;
	auto rad = DirectX::XMConvertToRadians(Brat);
	auto mat = DirectX::XMMatrixRotationZ(rad);

	DirectX::XMVECTOR Centor = DirectX::XMVectorSet(f4x4._41, f4x4._42, f4x4._43, 0);
	DirectX::XMVECTOR Origin = DirectX::XMVectorSet(0, 0, 0, 0);

	DirectX::XMMATRIX CtoO = DirectX::XMMatrixTranslationFromVector(Origin);
	DirectX::XMMATRIX OtoC = DirectX::XMMatrixTranslationFromVector(Centor);

	//--------------------

	//------  行列計算  ------
	World_ = Scale * CtoO * mat * OtoC;

	//削除用
	if (movedle > 100)
	{
		MyGame::GameObjectManager::Instance().DeleteGameObject(GetMyHandle());
		return;
	}
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