#pragma once
//------  Camera.h  ------
//------  参照  ------
#include"GameObject.h"

namespace MyGame {

	//@brief	------  カメラオブジェクト制御クラス  ------
	class CAMERA final :public GameObject
	{
	public:
		//@brief	データ構造体
		struct BufferData {
			DirectX::XMMATRIX World_{};
			DirectX::XMMATRIX Color_{};
		};
		//@brief	---  初期化関数  ---
		void Initialize()noexcept override;

		//@brief	---  UpDate()関数  ---
		virtual void UpDate()noexcept override;

		//@brief	---  描画指示設定  ---
		virtual void SetDrawCommand(const CommandList& List, UINT slot)noexcept override;

	private:
		DirectX::XMMATRIX view_{};        /// ビュー行列
		DirectX::XMMATRIX projection_{};  /// 射影行列

		// カメラのパラメータ
		DirectX::XMFLOAT3 Pos_{};  /// カメラの位置
		DirectX::XMFLOAT3 Target_{};    /// カメラの注視点
		DirectX::XMFLOAT3 Up_{};        /// カメラの上方向
	};
}