#pragma once
//------  GameObject.h  ------
//------  参照  ------
#include"../GameManager/PolygonManager.h"
#include"../Polygon/Triangle.h"
#include"../Polygon/Square.h"
#include"../Polygon/Square Pyramid.h"
#include"../DirectX/ConstantBuffer.h"
#include"../DirectX/CommandList.h"
#include<DirectXMath.h>


//@brief	------  オブジェクト制御基底クラス  ------
class GameObject
{
public:
	//@brief	データ構造体
	struct BufferData {
		DirectX::XMMATRIX World_{};
		DirectX::XMFLOAT4 Color_{};
	};

//------  オブジェクト設定関数群  ------

	GameObject() = default;
	virtual ~GameObject() = default;

	//@brief	---  初期化関数  ---
	virtual void Initialize()noexcept;

	//@brief	---  UpDate()関数  ---
	virtual void UpDate()noexcept = 0;

	//@brief	---  コンスタントバッファ作成関数  ---
	//@return	コンスタントバッファの作成可否
	virtual [[nodiscard]] bool CreateConstantBuffer()noexcept;

	//@brief	---  描画指示設定  ---
	virtual void SetDrawCommand(const CommandList& List, UINT slot)noexcept;

	//@brief	---  オブジェクトデータ設定関数  ---
	//@param	ポジション
	//@param	回転
	//@param	スケール
	//@param	カラー
	//@param	ポリゴン識別子
	void SetData(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rotate, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT4 color,UINT64 ID)noexcept;

	//@brief	---  クラス識別子設定関数  ---
	void SetClassID(UINT64 ID)noexcept;

	//@brief	---  個別識別子設定関数  ---
	void SetMyHandle(UINT64 ID)noexcept;

//------  参照関数群  ------

	//@brief	---  ワールド行列取得関数  ---
	//@return	World_
	[[nodiscard]] DirectX::XMMATRIX GetWorld()const noexcept;

	//@brief	---  カラー取得関数  ---
	//@return	Color_
	[[nodiscard]] DirectX::XMFLOAT4 GetColor()const noexcept;

	//@brief	---  クラス識別子取得関数  ---
	//@return	クラス識別子
	[[nodiscard]] UINT64 GetClassID()const noexcept;

	//@brief	---  個別識別子取得関数  ---
	//@return	個別識別子
	[[nodiscard]] UINT64 GetMyHandle()const noexcept;

	//@brief	---  あたり範囲取得関数  ---
	//@return	あたり範囲
	[[nodiscard]] float GetRadius()const noexcept;

//------  

protected:

	//@brief	---  コンスタントバッファ更新関数  ---
	template <class T>
	void UpDateConstantBuffer(const T& data)noexcept {
		std::byte* dst{};
		MyBuffer_.Get()->Map(0, nullptr, reinterpret_cast<void**>(&dst));
		memcpy_s(dst, sizeof(T), &data, sizeof(T));
		MyBuffer_.Get()->Unmap(0, nullptr);
	}


protected:
	DirectX::XMMATRIX	World_ = DirectX::XMMatrixIdentity();	//ワールド行列
	DirectX::XMFLOAT4	Color_ = DirectX::XMFLOAT4(1, 1, 1, 1);	//カラー
	ConstantBuffer		MyBuffer_{};							//コンスタントバッファ
	UINT64				PolygonID_{};							//ポリゴン識別子
	UINT64				MyHandle_{};							//個別識別子
	UINT64				ClassID_{};								//クラス識別子
	float				Radius_{};								//あたり範囲
	float				Move_{};								//移動速度
};