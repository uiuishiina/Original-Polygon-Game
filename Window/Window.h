#pragma once
//------  Window.h  ------
//------  参照  ------
#include<Windows.h>
#include<string>

class Window final 
{
public:
	Window() = default;
	//デストラクタ
	~Window() = default;
	//ウィンドウ作成
	[[nodiscard]] bool Create(HINSTANCE instance, int width, int height, std::string_view name)noexcept;
	//メッセージループ
	[[nodiscard]] bool MessegeLoop()const noexcept;
	//
private:
	HWND Handle_{};	//ウィンドウハンドル
};