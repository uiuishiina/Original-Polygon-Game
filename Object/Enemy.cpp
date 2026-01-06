//------  Enemy.cpp  ------
//------  参照  ------
#include"Enemy.h"
#include "../Window/Input.h"
#include<cassert>
float y = -10;

void Enemy::Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<Triangle>();//Square//Triangle
	SetData({ 0.0f,-10.0f, 30.0f }, { 0.0f, 0.0f, 0.0f }, { 10.0f, 10.0f, 1.0f }, { 1.0f, 0.0, 0.0f, 1 }, PolygonID_);
}

void Enemy::UpDate()noexcept {
	
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
	// ワールド行列の更新
	DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f);
	World_.r[3] = DirectX::XMVectorAdd(World_.r[3], temp);


	GameObject::UpDate();
}

//@brief	---  描画指示設定  ---
void Enemy :: SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	GameObject::SetDrawCommand(List,slot);
	PolygonManager::Instance().Draw(List, PolygonID_);
}