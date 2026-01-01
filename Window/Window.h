#pragma once
//------  Window.h  ------
//------  参照  ------
#include<Windows.h>
#include<string>

//@brief	------  Window 制御クラス  ------
class Window final 
{
public:
	//@brief	---  ウィンドウ取得関数  ---
	static Window& Instance()noexcept {
		static Window Instance;
		return Instance;
	}
	//@brief	ウィンドウ作成関数
	//@return	ウィンドウ作成の成否
	[[nodiscard]] bool Create(HINSTANCE instance, int width, int height, std::string_view name)noexcept;

	//@brief	メッセージループ関数
	//@return	ループ終了時false
	[[nodiscard]] bool MessegeLoop()const noexcept;

	//@brief	ウィンドウハンドル取得関数
	//@return	ウィンドウハンドル
	[[nodiscard]] HWND GetHandle()const noexcept;

	//@brief	ウィンドウサイズ取得関数
	//@return	ウィンドウサイズ
	[[nodiscard]] std::pair<int, int> GetSize()const noexcept;
private:
	Window() = default;
	//デストラクタ
	~Window() = default;

	HWND	Handle_{};	//ウィンドウハンドル
	int		Witdh_{};	//ウィンドウの横幅
	int		Height_{};	//ウィンドウの縦幅
};