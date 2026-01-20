//------  Enemy.cpp  ------
//------  参照  ------
#include"Enemy.h"
#include "../Window/Input.h"
#include<cassert>
float rat = 0;

void Enemy::Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<SquarePyramid>();//Square//Triangle//SquarePyramid//Cube//OutLineCube
	SetData({ 0.0f,0.0f, 30.0f }, { 0.0f, 0.5f, 0.0f }, { 10.0f, 10.0f, 10.0f }, { 1.0f, 1.0f, 1.0f, 1 }, PolygonID_);
}

void Enemy::UpDate()noexcept {
	
	constexpr float moveSpeed = 0.05f;
	// 入力処理
	/**/
	DirectX::XMFLOAT3 pos{};
	/*if (Input::instance().getKey('W')) {
		pos.y += moveSpeed;
	}
	if (Input::instance().getKey('S')) {
		pos.y -= moveSpeed;
	}
	if (Input::instance().getKey('A')) {
		
	}
	if (Input::instance().getKey('D')) {
		
	}*/
	// ワールド行列の更新

	//移動
	/*DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f);
	World_.r[3] = DirectX::XMVectorAdd(World_.r[3], temp);*/

	DirectX::XMFLOAT4X4 f4x4;
	DirectX::XMStoreFloat4x4(&f4x4, World_);//DirectX::XMMatrixIdentity()

	rat += 0.5f;
	//回転
	auto rad = DirectX::XMConvertToRadians(rat);
	auto mat = DirectX::XMMatrixRotationY(rad);
	
	DirectX::XMVECTOR Centor = DirectX::XMVectorSet(f4x4._41, f4x4._42, f4x4._43, 0);
	DirectX::XMVECTOR Origin = DirectX::XMVectorSet(0, 0, 0, 0);
	
	DirectX::XMMATRIX CtoO = DirectX::XMMatrixTranslationFromVector(Origin);
	DirectX::XMMATRIX OtoC = DirectX::XMMatrixTranslationFromVector(Centor);
	World_ = Scale * CtoO * mat * OtoC;

	GameObject::UpDate();
}

//@brief	---  描画指示設定  ---
void Enemy :: SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	GameObject::SetDrawCommand(List,slot);
	PolygonManager::Instance().Draw(List, PolygonID_);
}

//@brief	---  衝突時処理関数  ---
void Enemy :: OnHit()noexcept {
	Color_.y *= 0.95f;
	Color_.z *= 0.95f;
}