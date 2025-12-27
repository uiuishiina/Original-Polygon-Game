#pragma once
//------  CompileShader.h  ------
//------  参照  ------
#include"Device.h"

//@brief	------  シェーダー作成制御クラス  ------
class CompileShader final
{
public:
	CompileShader() = default;
	~CompileShader() = default;

	//@brief	---  シェーダー作成関数  ---
	//@return	シェーダーの作成可否
	[[nodiscard]] bool Create()noexcept;

	//@brief	---  頂点シェーダー取得関数  ---
	//@return	頂点シェーダーのポインター
	[[nodiscard]] ID3DBlob* GetVertex()const noexcept;

	//@brief	---  ピクセルシェーダー取得関数  ---
	//@return	ピクセルシェーダーのポインター
	[[nodiscard]] ID3DBlob* GetPixel()const noexcept;
private:
	Microsoft::WRL::ComPtr <ID3DBlob> VertexShader_{};
	Microsoft::WRL::ComPtr <ID3DBlob> PixelShader_{};
};