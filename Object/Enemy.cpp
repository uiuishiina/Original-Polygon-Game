//------  Enemy.cpp  ------
//------  éQè∆  ------
#include"Enemy.h"
#include<cassert>


void Enemy::Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<Square>();//Square//Triangle
}

void Enemy::UpDate()noexcept {
	GameObject::UpDate();
	DirectX::XMFLOAT3 pos{};
	// ïΩçsà⁄ìÆ
	DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x+1, pos.y, pos.z, 0.0f);
	World_.r[3] = DirectX::XMVectorAdd(World_.r[3], temp);
}

//@brief	---  ï`âÊéwé¶ê›íË  ---
void Enemy :: SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	//GameObject::SetDrawCommand(List,slot);
	PolygonManager::Instance().Draw(List, PolygonID_);
}