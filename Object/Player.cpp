//------  Player.cpp  ------
//------  参照  ------
#include"Player.h"
#include "../Window/Input.h"
#include<cassert>

void Player :: Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<Triangle>();//Square//Triangle//SquarePyramid//Cube//OutlineCube
	SetData({ 0.0f,0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0, 0.0f, 1 }, PolygonID_);
	//MyGame::GameObjectManager::Instance().AddComponent<Collision>();
}

//@brief	---  UpDate()関数  ---
void Player :: UpDate()noexcept {
	constexpr float moveSpeed = 0.05f;
	// 入力処理
	/**/
	DirectX::XMFLOAT3 pos{};
	if (Input::instance().getKey('W')) {
		pos.z += moveSpeed;
	}
	if (Input::instance().getKey('S')) {
		pos.z -= moveSpeed;
	}
	if (Input::instance().getKey('A')) {
		pos.x -= moveSpeed;
	}
	if (Input::instance().getKey('D')) {
		pos.x += moveSpeed;
	}
	if (Input::instance().getTrigger('B')) {
		MyGame::GameObjectManager::Instance().CreateGameObject<Bullet>(MyHandle_);
	}
	// ワールド行列の更新

	DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f);
	World_.r[3] = DirectX::XMVectorAdd(World_.r[3], temp);

	GameObject::UpDate();
}

//@brief	---  描画指示設定  ---
void Player :: SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	GameObject::SetDrawCommand(List, slot);
	PolygonManager::Instance().Draw(List, PolygonID_);
}