//------  Camera.cpp  ------
//------  参照  ------
#include"Camera.h"
#include<cassert>
namespace {
    // 定数
    constexpr float eyeMoveSpeed_ = 0.06f;  // カメラ移動速度
    constexpr float destTargetToView_ = -5.0f;  // 注視点からカメラまでの距離
}

namespace MyGame {

	//@brief	---  初期化関数  ---
	void CAMERA :: Initialize()noexcept {
		GameObject::Initialize();
        // カメラの位置を設定
        Pos_ = DirectX::XMFLOAT3(0.0f, 1.5f, destTargetToView_);
        // カメラの注視点を設定
        Target_ = DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f);
        // カメラの上方向を設定
        Up_ = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

        // プロジェクション行列の設定
        projection_ = DirectX::XMMatrixPerspectiveFovLH(
            DirectX::XM_PIDIV4,  // 視野角45度
            1280.0f / 720.0f,    // アスペクト比
            0.1f,                // ニアクリップ
            100.0f               // ファークリップ
        );
	}

    //@brief	---  UpDate()関数  ---
    void CAMERA :: UpDate()noexcept{
        // ビュー行列の計算
        view_ = DirectX::XMMatrixLookAtLH(
            DirectX::XMLoadFloat3(&Pos_),
            DirectX::XMLoadFloat3(&Target_),
            DirectX::XMLoadFloat3(&Up_));
    }
}