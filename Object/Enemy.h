#pragma once
//------  Enemy.h  ------
//------  QÆ  ------
#include"GameObject.h"

class Enemy :public GameObject
{
public:
	virtual void Initialize()noexcept override;

	//@brief	---  UpDate()ŠÖ”  ---
	virtual void UpDate()noexcept override;

	//@brief	---  •`‰æw¦İ’è  ---
	virtual void SetDrawCommand(const CommandList& List, UINT slot)noexcept override;

	//@brief	---  Õ“Ëˆ—ŠÖ”  ---
	void OnHit()noexcept override;
};