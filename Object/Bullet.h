#pragma once
//------  Bullet.h  ------
//------  参照  ------
#include"../GameManager/GameObjectManager.h"
#include"GameObject.h"
#include"Enemy.h"

//@brief	------  球オブジェクト制御クラス  ------
class Bullet final :public GameObject
{
public:
	virtual void Initialize()noexcept override;

	//@brief	---  UpDate()関数  ---
	virtual void UpDate()noexcept override;

	//@brief	---  描画指示設定  ---
	virtual void SetDrawCommand(const CommandList& List, UINT slot)noexcept override;

	//@brief	---  衝突相手取得関数  ---
	[[nodiscard]] UINT64 HitClassHandle()noexcept override;

	//@brief	---  衝突時処理関数  ---
	void OnHit()noexcept override;
};