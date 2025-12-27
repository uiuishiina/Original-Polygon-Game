#pragma once
//------  PiplineState.h  ------
//------  参照  ------
#include"Device.h"
#include"CompileShader.h"
#include"RootSignature.h"

//@brief	------  パイプラインステートオブジェクト制御クラス  ------
class Pipline final
{
public:
	Pipline() = default;
	~Pipline() = default;

	//@brief	---  パイプラインステート作成関数  ---
	//@return	パイプラインステートの作成可否
	[[nodiscard]] bool Create(const CompileShader& shader, const RootSignature& root)noexcept;

	//@brief	--- パイプラインステート取得関数  ---
	//@return	パイプラインステートのポインター
	[[nodiscard]] ID3D12PipelineState* Get()const noexcept;
private:
	Microsoft::WRL::ComPtr <ID3D12PipelineState> State_{};
};
