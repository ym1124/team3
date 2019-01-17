#include "DxLib.h"
#include "common.h"
#include "scene.h"

#include "src\imgui.h"
#include "src\imgui_impl_dxlib.h"

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);

	// ウインドウモードに変更
	ChangeWindowMode(1);

	//ウインドウのサイズを自由に変更出来るようにする
	SetWindowSizeChangeEnableFlag(TRUE, FALSE);

	// 描画可能サイズをディスプレイのサイズに
	SetGraphMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 32);    //メインウインドウのクライアント領域のサイズを設定する

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	SetMainWindowText("TEAM03kadai");

	SetWindowStyleMode(10);



#if defined(DEBUG) | defined(_DEBUG)

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//SRand((unsigned int)time(NULL));

	//SetDrawMode(DX_DRAWMODE_NEAREST);


	//SetWaitVSyncFlag(FALSE);

	if (DxLib_Init() == -1) return -1;    // ＤＸライブラリ初期化処理 エラーが起きたら終了



	SetDrawScreen(DX_SCREEN_BACK);

	// メッセージをフックするウインドウプロージャを登録する
	//注意：DxLib_Initを呼んだ後でないと　登録されない。
	SetHookWinProc(WndProc);
	//ＩＭＥを使用する
	SetUseIMEFlag(TRUE);

	// Setup ImGui binding
	ImGui_ImplDxLib_Init();


	bool show_test_window = false;
	bool show_another_window = false;
	ImVec4 clear_col = ImColor(0, 0, 0);
	SetBackgroundColor((int)(clear_col.x * 255.0f),
		(int)(clear_col.y * 255.0f),
		(int)(clear_col.z * 255.0f));

	sceneManager scenemanager;
	//SoundInit();
	scenemanager.changeScene(scenemanager.TITLE);


	while (gameexit && ProcessMessage() == 0)
	{
		ClearDrawScreen();// 裏画面のデータを全て削除

		InputKey();

		//InputJoypad();

		scenemanager.execute();

		ScreenFlip();

	}

	ImGui_ImplDxLib_Shutdown();

	DxLib_End();                                            // ＤＸライブラリ使用の終了処理
	return 0;                                               // ソフトの終了
}


LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplDxLib_WndProcHandler(wnd, msg, wParam, lParam)) {
		SetUseHookWinProcReturnValue(TRUE);
		return 1;
	}

	//IME関連はOSに任せる
	switch (msg)
	{
		//WM_IME_SETCONTEXTを受け取ったときに
		//lParam = 0;とするとIME関連の表示が行われなくなります。
	case WM_IME_SETCONTEXT:
	case WM_IME_STARTCOMPOSITION:
	case WM_IME_ENDCOMPOSITION:
	case WM_IME_COMPOSITION:
	case WM_IME_NOTIFY:
	case WM_IME_REQUEST:
		SetUseHookWinProcReturnValue(TRUE);
		return DefWindowProc(wnd, msg, wParam, lParam);

	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) { // Disable ALT application menu
			SetUseHookWinProcReturnValue(TRUE);
			return 0;
		}
		break;
	}

	return 0;
}
