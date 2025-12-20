//------  Entry.cpp  ------
//------  参照  ------
#include<cassert>
//------  Window  ------
#include"../Window/Window.h"

//------  名前空間  ------
namespace {
	constexpr std::string_view APP_NAME = "MyGame";
};

//------  アプリケーション  ------
class Application final 
{
public:
	Application() = default;
	~Application() = default;

	//アプリケーション初期化関数
	[[nodiscard]] bool Initialize(HINSTANCE instance)noexcept {

		//ウィンドウ作成
		if (!Window_.Create(instance, 1280, 720, APP_NAME)) {
			assert(false && "ウィンドウズの作成に失敗しました(App)");
			return false;
		}

		//アプリケーション作成完了
		return true;
	}

	//アプリケーションループ関数
	void Loop()noexcept {
		while (Window_.MessegeLoop()) {

		}
	}
private:
	//------  各クラスのインスタンス  ------
	Window Window_{};
};

//------  ゲームメイン関数  ------
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