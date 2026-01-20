//------  Entry.cpp  ------
//------  参照  ------
#include<cassert>
#include <memory>
//------  Window  ------
#include"../Window/Window.h"
//------  DirectX  ------
#include"../DirectX/DXGI.h"
#include"../DirectX/Device.h"
#include"../DirectX/CommandQueue.h"
#include"../DirectX/SwapChain.h"
#include"../DirectX/RenderTarget.h"
#include"../DirectX/CommandAllocator.h"
#include"../DirectX/CommandList.h"
#include"../DirectX/Fence.h"
#include"../DirectX/RootSignature.h"
#include"../DirectX/CompileShader.h"
#include"../DirectX/PiplineState.h"
#include"../DirectX/DepthBuffer.h"
#include"../DirectX/ConstantBuffer.h"
//------  Polygon  ------
#include"../Polygon/Triangle.h"
#include"../Polygon/Square.h"
//------  GameManager  ------
#include"../GameManager/DescriptorManager.h"
#include"../GameManager/PolygonManager.h"
#include"../GameManager/GameObjectManager.h"
//------  Object  ------
#include"../Object/Camera.h"
#include"../Object/Enemy.h"
#include"../Object/Bullet.h"
#include"../Object/Player.h"
//------  名前空間  ------

namespace {
	constexpr std::string_view APP_NAME = "MyGame";
};

//@brief	------  アプリケーション制御クラス  ------
class Application final 
{
public:
	Application() = default;
	~Application() = default;

	//@brief	---  アプリケーション初期化関数  ---
	[[nodiscard]] bool Initialize(HINSTANCE instance)noexcept {

		//ウィンドウ作成
		if (!Window::Instance().Create(instance, 1280, 720, APP_NAME)) {
			assert(false && "ウィンドウズの作成に失敗しました(App)");
			return false;
		}

		//デバイス作成
		if (!Device::Instance().Create()) {
			assert(false && "デバイスの作成に失敗しました(App)");
			return false;
		}

		//コマンドキュー作成
		if (!Queue_.Create()) {
			assert(false && "コマンドキューの作成に失敗しました(App)");
			return false;
		}

		//スワップチェイン作成
		if (!SwapChain_.Create(Queue_)) {
			assert(false && "スワップチェインの作成に失敗しました(App)");
			return false;
		}
		// 定数バッファ用ディスクリプタヒープの生成
		if (!DHManager::Instance().Create(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 5, true)) {
			assert(false && "定数バッファ用ディスクリプタヒープの作成に失敗しました");
			return false;
		}

		//描画用ディスクリプターヒープ作成
		if (!DHManager::Instance().Create(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, SwapChain_.GetDesc().BufferCount)) {
			assert(false && "ディスクリプターヒープの作成に失敗しました(App)");
			return false;
		}

		// デプスバッファ用ディスクリプタヒープの作成
		if (!DHManager::Instance().Create(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1)) {
			assert(false && "デプスバッファ用ディスクリプタヒープの作成に失敗しました");
			return false;
		}

		//レンダーターゲット作成
		if (!RenderTarget_.Create(SwapChain_)) {
			assert(false && "レンダーターゲットの作成に失敗しました(App)");
			return false;
		}

		//デプスバッファ作成
		if (!Depth_.Create()) {
			assert(false && "デプスバッファの作成に失敗しました(App)");
			return false;
		}

		//コマンドアロケーター作成
		for (int i = 0; i < 2; i++) {
			if (!Allocator_[i].Create(D3D12_COMMAND_LIST_TYPE_DIRECT)) {
				assert(false && "コマンドアロケーターの作成に失敗しました(App)");
				return false;
			}
		}

		//コマンドリスト作成
		if (!CommandList_.Create(Allocator_[0])) {
			assert(false && "コマンドリストの作成に失敗しました(App)");
			return false;
		}

		//フェンス作成
		if (!Fence_.Create()) {
			assert(false && "フェンスの作成に失敗しました(App)");
			return false;
		}

		//ルートシグネチャ作成
		if (!Root_.Create()) {
			assert(false && "ルートシグネチャの作成に失敗しました(App)");
			return false;
		}

		//シェーダー作成
		if (!Shader_.Create()) {
			assert(false && "シェーダーの作成に失敗しました(App)");
			return false;
		}
		
		//"パイプラインステートオブジェクト作成
		if (!Pipline_.Create(Shader_, Root_)) {
			assert(false && "パイプラインステートの作成に失敗しました(App)");
			return false;
		}
		
		MyGame::GameObjectManager::Instance().CreateGameObject<MyGame::CAMERA>();
		
		MyGame::GameObjectManager::Instance().CreateGameObject<Player>();

		//アプリケーション作成完了
		return true;
	}

	//@brief	---  アプリケーションループ関数  ---
	void Loop()noexcept {
		while (Window::Instance().MessegeLoop()) {

			MyGame::GameObjectManager::Instance().UpDate();

			//現在のバッファインデックスを取得
			const auto BufferIndex = SwapChain_.Get()->GetCurrentBackBufferIndex();
			//処理が終了していないなら待機
			if (FenceValue_[BufferIndex] != 0) {
				Fence_.Wait(FenceValue_[BufferIndex]);
			}

			//リセット
			Allocator_[BufferIndex].Reset();
			CommandList_.Reset(Allocator_[BufferIndex]);

			//リソースバリアー変更
			auto PtoRT = ResourseBarrier(RenderTarget_.Get(BufferIndex), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
			CommandList_.Get()->ResourceBarrier(1, &PtoRT);

			//レンダーターゲット設定
			D3D12_CPU_DESCRIPTOR_HANDLE Handles[] = {RenderTarget_.GetHandle(BufferIndex)};
			auto Handle = Depth_.GetHandle();
			CommandList_.Get()->OMSetRenderTargets(1, Handles, false, &Handle);

			//レンダーターゲットクリア
			const float Color[] = { 0.0f,0.0f,0.0f,1.0f };
			CommandList_.Get()->ClearRenderTargetView(Handles[0], Color, 0, nullptr);

			// デプスバッファのクリア
			CommandList_.Get()->ClearDepthStencilView(Handle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

			//------  描画指示箇所  ------
			{
				//
				CommandList_.Get()->SetPipelineState(Pipline_.Get());
				//
				CommandList_.Get()->SetGraphicsRootSignature(Root_.Get());

				// ビューポートの設定
				const auto [w, h] = Window::Instance().GetSize();
				D3D12_VIEWPORT viewport{};
				viewport.TopLeftX = 0.0f;
				viewport.TopLeftY = 0.0f;
				viewport.Width = static_cast<float>(w);
				viewport.Height = static_cast<float>(h);
				viewport.MinDepth = 0.0f;
				viewport.MaxDepth = 1.0f;
				CommandList_.Get()->RSSetViewports(1, &viewport);

				// シザー矩形の設定
				D3D12_RECT scissorRect{};
				scissorRect.left = 0;
				scissorRect.top = 0;
				scissorRect.right = w;
				scissorRect.bottom = h;
				CommandList_.Get()->RSSetScissorRects(1, &scissorRect);

				// コンスタントバッファ用ディスクリプタヒープの設定
				ID3D12DescriptorHeap * p[] = { DHManager::Instance().Get(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV) };
				CommandList_.Get()->SetDescriptorHeaps(1, p);

				MyGame::GameObjectManager::Instance().Draw(CommandList_);

			}

			//リソースバリアー変更
			auto RTtoP = ResourseBarrier(RenderTarget_.Get(BufferIndex), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
			CommandList_.Get()->ResourceBarrier(1, &RTtoP);

			//コマンドリストクローズ
			CommandList_.Get()->Close();

			//コマンドキューに送信
			ID3D12CommandList* Lists[] = {CommandList_.Get()};
			Queue_.Get()->ExecuteCommandLists(_countof(Lists),Lists);

			//プレゼント
			SwapChain_.Get()->Present(1, 0);

			//更新処理
			Queue_.Get()->Signal(Fence_.Get(), NextFenceValue_);
			FenceValue_[BufferIndex] = NextFenceValue_;
			NextFenceValue_++;
		}
	}
private:
	//@brief	---  リソースバリア設定変更関数  ---
	//@param	リソースバリア
	//@param	変更前のリソースステート
	//@param	変更後のリソースステート
	D3D12_RESOURCE_BARRIER ResourseBarrier(ID3D12Resource* Resouece, D3D12_RESOURCE_STATES from, D3D12_RESOURCE_STATES to)noexcept {
		D3D12_RESOURCE_BARRIER b{};
		b.Type						= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		b.Flags						= D3D12_RESOURCE_BARRIER_FLAG_NONE;
		b.Transition.pResource		= Resouece;
		b.Transition.StateBefore	= from;
		b.Transition.StateAfter		= to;
		b.Transition.Subresource	= D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		return b;
	}

private:
	//------  各クラスのインスタンス  ------

	CommandQueue		Queue_{};		//@brief	コマンドキューインスタンス
	SwapChain			SwapChain_{};	//@brief	スワップチェインインスタンス
	RenderTarget		RenderTarget_{};//@brief	レンダーターゲットインスタンス
	CommandAllocator	Allocator_[2]{};//@brief	コマンドアロケーターインスタンス
	CommandList			CommandList_{};	//@brief	コマンドリストインスタンス
	Fence				Fence_{};		//@broef	フェンスインスタンス
	RootSignature		Root_{};		//@brief	
	CompileShader		Shader_{};		//@brief	
	Pipline				Pipline_{};		//@brief	
	DepthBuffer			Depth_{};
	ConstantBuffer		Constant_{};
	Enemy				E_{};
	
	UINT64 FenceValue_[2]{};
	UINT64 NextFenceValue_ = 1;
};

//@brief	------  ゲームメイン関数  ------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow) {

	Application App;
	
	//アプリケーション作成
	if (!App.Initialize(hInstance)) {
		assert(false && "アプリケーションの作成に失敗");
	}
	//アプリケーションループ開始
	App.Loop();

	return 0;
}