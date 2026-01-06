//------  Bullet.cpp  ------
//------  éQè∆  ------
#include"Bullet.h"

void Bullet::Initialize()noexcept {
	GameObject::Initialize();
	PolygonID_ = PolygonManager::Instance().Create<Square>();//Square//Triangle
	SetData({0.0f, 1.0f, 0.1f}, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1, 0.0f, 1 }, PolygonID_);
}

void Bullet::UpDate()noexcept {
	GameObject::UpDate();
}

//@brief	---  ï`âÊéwé¶ê›íË  ---
void Bullet::SetDrawCommand(const CommandList& List, UINT slot)noexcept {
	GameObject::SetDrawCommand(List, slot);
	PolygonManager::Instance().Draw(List, PolygonID_);
}