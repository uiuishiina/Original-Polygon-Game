//------  Window.cpp  ------
//------  参照  ------
#include"Window.h"
#include"Input.h"
#include<cassert>
//------  名前空間  -----
namespace {
	//@brief	---  ウィンドウプロシージャ  ---
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
}

//@brief	---  ウィンドウ作成関数  ---
//@return	ウィンドウ作成の成否
[[nodiscard]] bool Window :: Create(HINSTANCE instance, int width, int height, std::string_view name)noexcept {

	//ウィンドウ定義
	WNDCLASS wc{};
	wc.lpfnWndProc		= WindowProc;							//ウィンドウプロシージャ
	wc.hInstance		= instance;								//HINSTANCE
	wc.lpszClassName	= name.data();							//ウィンドウクラス名
	wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);		//
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);	//初期ウィンドウ背景
	//ウィンドウクラス登録
	RegisterClass(&wc);
	//ウィンドウ作成
	Handle_ = CreateWindow(
		wc.lpszClassName,	//ClassName
		wc.lpszClassName,	//WindowName
		WS_OVERLAPPEDWINDOW,//ウィンドウタイプ
		CW_USEDEFAULT,		//ウィンドウ出現位置x
		CW_USEDEFAULT,		//ウィンドウ出現位置y
		width,				//ウィンドウ横幅
		height,				//ウィンドウ縦幅
		nullptr,			//hWndParent
		nullptr,			//hMenu
		instance,			//HINSTANCE
		nullptr				//lpParam
	);
	
	if (!Handle_) {
		assert(false && "ウィンドウ作成失敗");
		return false;
	}
	//ウィンドウ表示
	ShowWindow(Handle_, SW_SHOW);
	//ウィンドウ更新
	UpdateWindow(Handle_);
	Witdh_ = width;
	Height_ = height;
	return true;
}

//@brief	---  メッセージループ関数  ---
[[nodiscard]] bool Window :: MessegeLoop()const noexcept {
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}
		//メッセージ処理
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// キー情報の取得
		static byte keyState[256]{};
		if (GetKeyboardState(keyState)) {
			// キー情報取得に成功したら、Input クラスに情報を渡す
			Input::instance().updateKeyState(keyState);
		}
	}
	return true;
}

//@brief	---  ウィンドウハンドル取得関数  ---
//@return	ウィンドウハンドル
[[nodiscard]] HWND Window :: GetHandle()const noexcept {
	assert(Handle_ && "ウィンドウハンドル未作成");
	return Handle_;
}

//@brief	---  ウィンドウサイズ取得関数  ---
//@return	ウィンドウサイズ
[[nodiscard]] std::pair<int, int> Window :: GetSize()const noexcept {
	return { Witdh_, Height_ };
}