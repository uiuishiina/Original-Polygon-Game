//------  Enemy.cpp  ------
//------  参照  ------
#include"Enemy.h"
#include "../Window/Input.h"
#include<cassert>
float y = -10;

void Enemy::Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<SquarePyramid>();//Square//Triangle//SquarePyramid//Cube//OutlineCube
	SetData({ 0.0f,0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0, 0.0f, 1 }, PolygonID_);
}

void Enemy::UpDate()noexcept {
	
	constexpr float moveSpeed = 0.05f;
	// 入力処理
	/**/
	DirectX::XMFLOAT3 pos{};
	if (Input::instance().getKey('W')) {
		pos.y += moveSpeed;
	}
	if (Input::instance().getKey('S')) {
		pos.y -= moveSpeed;
	}
	if (Input::instance().getKey('A')) {
		
	}
	if (Input::instance().getKey('D')) {
		
	}
	// ワールド行列の更新

	DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f);
	World_.r[3] = DirectX::XMVectorAdd(World_.r[3], temp);
	
	auto rad = DirectX::XMConvertToRadians(0.5f);
	auto mat = DirectX::XMMatrixRotationY(rad);
	World_ = DirectX::XMMatrixMultiply(World_, mat);

	GameObject::UpDate();
}

//@brief	---  描画指示設定  ---
void Enemy :: SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	GameObject::SetDrawCommand(List,slot);
	PolygonManager::Instance().Draw(List, PolygonID_);
}

//@brief	---  衝突時処理関数  ---
void Enemy :: OnHit()noexcept {

}