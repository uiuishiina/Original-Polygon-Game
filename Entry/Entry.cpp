//------  Entry.cpp  ------
//------  参照  ------
#include<cassert>
//------  Window  ------
#include"../Window/Window.h"
//------  DirectX  ------
#include"../DirectX/DXGI.h"
#include"../DirectX/Device.h"
#include"../DirectX/CommandQueue.h"
#include"../DirectX/SwapChain.h"
#include"../DirectX/Descriptor_Heap.h"
#include"../DirectX/RenderTarget.h"
#include"../DirectX/CommandAllocator.h"
#include"../DirectX/CommandList.h"
#include"../DirectX/Fence.h"
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
		if (!Window_.Create(instance, 1280, 720, APP_NAME)) {
			assert(false && "ウィンドウズの作成に失敗しました(App)");
			return false;
		}

		//DXGI作成
		if (!DXGI_.SetDisplayAdapter()) {
			assert(false && "DXGIの作成に失敗しました(App)");
			return false;
		}

		//デバイス作成
		if (!Device_.Create(DXGI_)) {
			assert(false && "デバイスの作成に失敗しました(App)");
			return false;
		}

		//コマンドキュー作成
		if (!Queue_.Create(Device_)) {
			assert(false && "コマンドキューの作成に失敗しました(App)");
			return false;
		}

		//スワップチェイン作成
		if (!SwapChain_.Create(DXGI_, Queue_, Window_)) {
			assert(false && "スワップチェインの作成に失敗しました(App)");
			return false;
		}

		//ディスクリプターヒープ作成
		if (!Heap_.Create(Device_, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, SwapChain_.GetDesc().BufferCount)) {
			assert(false && "ディスクリプターヒープの作成に失敗しました(App)");
			return false;
		}

		//レンダーターゲット作成
		if (!RenderTarget_.Create(Device_, SwapChain_, Heap_)) {
			assert(false && "レンダーターゲットの作成に失敗しました(App)");
			return false;
		}

		//コマンドアロケーター作成
		for (int i = 0; i < 2; i++) {
			if (!Allocator_[i].Create(Device_, D3D12_COMMAND_LIST_TYPE_DIRECT)) {
				assert(false && "コマンドアロケーターの作成に失敗しました(App)");
				return false;
			}
		}

		//コマンドリスト作成
		if (!CommandList_.Create(Device_, Allocator_[0])) {
			assert(false && "コマンドリストの作成に失敗しました(App)");
			return false;
		}

		//フェンス作成
		if (!Fence_.Create(Device_)) {
			assert(false && "フェンスの作成に失敗しました(App)");
			return false;
		}

		//アプリケーション作成完了
		return true;
	}

	//@brief	---  アプリケーションループ関数  ---
	void Loop()noexcept {
		while (Window_.MessegeLoop()) {

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
			D3D12_CPU_DESCRIPTOR_HANDLE Handles[] = {RenderTarget_.GetHandle(Device_,Heap_,BufferIndex)};
			CommandList_.Get()->OMSetRenderTargets(1, Handles, false, nullptr);

			//レンダーターゲットクリア
			const float Color[] = { 0.0f,0.0f,0.0f,1.0f };
			CommandList_.Get()->ClearRenderTargetView(Handles[0], Color, 0, nullptr);

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

	Window				Window_{};		//@brief	ウィンドウインスタンス
	DXGI				DXGI_{};		//@brief	DXGIインスタンス
	Device				Device_{};		//@brief	デバイスインスタンス
	CommandQueue		Queue_{};		//@brief	コマンドキューインスタンス
	SwapChain			SwapChain_{};	//@brief	スワップチェインインスタンス
	DescriptorHeap		Heap_{};		//@brief	ディスクリプターヒープインスタンス
	RenderTarget		RenderTarget_{};//@brief	レンダーターゲットインスタンス
	CommandAllocator	Allocator_[2]{};//@brief	コマンドアロケーターインスタンス
	CommandList			CommandList_{};	//@brief	コマンドリストインスタンス
	Fence				Fence_{};		//@broef	フェンスインスタンス

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