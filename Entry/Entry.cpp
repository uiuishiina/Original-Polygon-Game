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

		//アプリケーション作成完了
		return true;
	}

	//@brief	---  アプリケーションループ関数  ---
	void Loop()noexcept {
		while (Window_.MessegeLoop()) {

		}
	}
private:
	//------  各クラスのインスタンス  ------

	Window			Window_{};		//@brief	ウィンドウインスタンス
	DXGI			DXGI_{};		//@brief	DXGIインスタンス
	Device			Device_{};		//@brief	デバイスインスタンス
	CommandQueue	Queue_{};		//@brief	コマンドキューインスタンス
	SwapChain		SwapChain_{};	//@brief	スワップチェインインスタンス
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