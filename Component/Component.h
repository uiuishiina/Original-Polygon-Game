#pragma once
//------  Component.h  ------
//------  参照  ------
#include"../Object/GameObject.h"

//@brief	------  コンポーネント基底クラス  ------
class Component
{
public:
	Component() = default;
	virtual ~Component() = default;
	//@brief	---  初期化関数  ---
	virtual void Initialize()noexcept;

	////@brief	---  UpDate()関数  ---
	//virtual void UpDate(std::unordered_map<UINT64, std::unique_ptr<GameObject>>& GameObject_)noexcept = 0;

	////@btier	---  LateUpDate()関数  ---
	//virtual void LateUpDate(std::unordered_map<UINT64, std::unique_ptr<GameObject>>& GameObject_)noexcept = 0;

	//@brief	---  オブジェクトハンドルセット関数  ---
	virtual void SetUseComponent(UINT64 Handle)noexcept {
		UseComponentHandle_.emplace_back(Handle);
	}

	//@brief	---  オブジェクトハンドル初期化関数  ---
	virtual void ClearUseComponent()noexcept {
		UseComponentHandle_.clear();
	}
protected:
	std::vector<UINT64> UseComponentHandle_{};	//コンポーネントを適用するオブジェクトハンドル
};