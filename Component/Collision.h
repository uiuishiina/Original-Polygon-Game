#pragma once
//------  Collision.h  ------
//------  参照  ------
#include"Component.h"

//@brief	---  衝突判定コンポーネントクラス   ---
class Collision : public Component
{
public:
	Collision() = default;
	~Collision()override = default;

	////@brief	---  UpDate()関数  ---
	//void UpDate(std::unordered_map<UINT64, std::unique_ptr<GameObject>>& GameObject_)noexcept override;

	////@btier	---  LateUpDate()関数  ---
	//void LateUpDate(std::unordered_map<UINT64, std::unique_ptr<GameObject>>& GameObject_)noexcept override;

private:
};