//------  Bullet.cpp  ------
//------  éQè∆  ------
#include"Bullet.h"
#include<cassert>

void Bullet::Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<Square>();//Square//Triangle
}

void Bullet::UpDate()noexcept {

	DirectX::XMFLOAT3 pos{};
	// ïΩçsà⁄ìÆ
	DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x + 1, pos.y, pos.z, 0.0f);
	World_.r[3] = DirectX::XMVectorAdd(World_.r[3], temp);
	GameObject::UpDate();
}

//@brief	---  ï`âÊéwé¶ê›íË  ---
void Bullet::SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	GameObject::SetDrawCommand(List, slot);
	PolygonManager::Instance().Draw(List, PolygonID_);
}