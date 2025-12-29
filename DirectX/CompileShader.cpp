//------  CompileShader.cpp  ------
//------  参照  ------
#include"CompileShader.h"
#include<cassert>
#include<string>
#include<d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")

//@brief	---  シェーダー作成関数  ---
	//@return	シェーダーの作成可否
[[nodiscard]] bool CompileShader :: Create()noexcept {

	//シェーダーの読み取りパス作成
	const std::string FilePath = "../Shader/VertexShader.hlsl";
	const std::wstring Temp = std::wstring(FilePath.begin(), FilePath.end());

	//シェーダーのコンパイル1
	ID3DBlob* Errer{};
	auto hr = D3DCompileFromFile(Temp.data(), nullptr, nullptr, "vs", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &VertexShader_, &Errer);
	if (FAILED(hr)) {
		char* p = static_cast<char*>(Errer->GetBufferPointer());
		assert(false && "頂点シェーダーのコンパイルに失敗");
		return false;
	}
	hr = D3DCompileFromFile(Temp.data(), nullptr, nullptr, "ps", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &PixelShader_, &Errer);
	if (FAILED(hr)) {
		char* p = static_cast<char*>(Errer->GetBufferPointer());
		assert(false && "ピクセルシェーダーのコンパイルに失敗");
		return false;
	}

	if (Errer) {
		Errer->Release();
	}
	return true;
}

//@brief	---  頂点シェーダー取得関数  ---
//@return	頂点シェーダーのポインター
[[nodiscard]] ID3DBlob* CompileShader :: GetVertex()const noexcept {
	assert(VertexShader_ && "頂点シェーダー未作成");
	return VertexShader_.Get();
}

//@brief	---  ピクセルシェーダー取得関数  ---
//@return	ピクセルシェーダーのポインター
[[nodiscard]] ID3DBlob* CompileShader :: GetPixel()const noexcept {
	assert(PixelShader_ && "ピクセルシェーダー未作成");
	return PixelShader_.Get();
}