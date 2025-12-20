//------  Window.cpp  ------
//------  参照  ------
#include"Window.h"
#include<cassert>
//------  名前空間  -----
namespace {
	//ウィンドウプロシージャ
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
}

//ウィンドウ作成関数
[[nodiscard]] bool Window :: Create(HINSTANCE instance, int width, int height, std::string_view name)noexcept {

	//ウィンドウ定義
	WNDCLASS wc{};
	wc.lpfnWndProc		= WindowProc;
	wc.hInstance		= instance;
	wc.lpszClassName	= name.data();
	wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	//ウィンドウクラス登録
	RegisterClass(&wc);
	//ウィンドウ作成
	Handle_ = CreateWindow(
		wc.lpszClassName,	//ClassName
		wc.lpszClassName,	//WindowName
		WS_OVERLAPPEDWINDOW,//ウィンドウタイプ
		CW_USEDEFAULT,		//ウィンドウ出現位置x
		CW_USEDEFAULT,		//ウィンドウ出現位置y
		width,				//ウィンドウ縦幅
		height,				//ウィンドウ横幅
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

	return true;
}

//メッセージループ関数
[[nodiscard]] bool Window :: MessegeLoop()const noexcept {
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return false;
		}
		//メッセージ処理
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}