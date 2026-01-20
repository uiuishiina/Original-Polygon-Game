#pragma once
//------  Player.h  ------
//------  éQè∆  ------
#include"../GameManager/GameObjectManager.h"
#include"GameObject.h"
#include"Bullet.h"

class Player :public GameObject
{
public:
	void Initialize()noexcept override;

	//@brief	---  UpDate()ä÷êî  ---
	void UpDate()noexcept override;

	//@brief	---  ï`âÊéwé¶ê›íË  ---
	void SetDrawCommand(const CommandList& List, UINT slot)noexcept override;
};