//------  GameObject.cpp  ------
//------  参照  ------
#include"GameObject.h"


//@brief	---  初期化関数  ---
void GameObject :: Initialize()noexcept {
	CreateConstantBuffer();
}

//@brief	---  コンスタントバッファ作成関数  ---
//@return	コンスタントバッファの作成可否
[[nodiscard]] bool GameObject :: CreateConstantBuffer()noexcept {
	return true;
}