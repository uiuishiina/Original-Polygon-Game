#pragma once
//------  Enemy.h  ------
//------  éQè∆  ------
#include"GameObject.h"

class Enemy :public GameObject
{
public:
	virtual void Initialize()noexcept override;

	//@brief	---  UpDate()ä÷êî  ---
	virtual void UpDate()noexcept override;

	//@brief	---  ï`âÊéwé¶ê›íË  ---
	virtual void SetDrawCommand(const CommandList& List, UINT slot)noexcept override;
};