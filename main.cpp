#include "DxLib.h"
#include "common.h"
#include "scene.h"

#include "src\imgui.h"
#include "src\imgui_impl_dxlib.h"

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);

	// �E�C���h�E���[�h�ɕύX
	ChangeWindowMode(1);

	//�E�C���h�E�̃T�C�Y�����R�ɕύX�o����悤�ɂ���
	SetWindowSizeChangeEnableFlag(TRUE, FALSE);

	// �`��\�T�C�Y���f�B�X�v���C�̃T�C�Y��
	SetGraphMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 32);    //���C���E�C���h�E�̃N���C�A���g�̈�̃T�C�Y��ݒ肷��

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	SetMainWindowText("TEAM03kadai");

	SetWindowStyleMode(10);



#if defined(DEBUG) | defined(_DEBUG)

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//SRand((unsigned int)time(NULL));

	//SetDrawMode(DX_DRAWMODE_NEAREST);


	//SetWaitVSyncFlag(FALSE);

	if (DxLib_Init() == -1) return -1;    // �c�w���C�u�������������� �G���[���N������I��



	SetDrawScreen(DX_SCREEN_BACK);

	// ���b�Z�[�W���t�b�N����E�C���h�E�v���[�W����o�^����
	//���ӁFDxLib_Init���Ă񂾌�łȂ��Ɓ@�o�^����Ȃ��B
	SetHookWinProc(WndProc);
	//�h�l�d���g�p����
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
		ClearDrawScreen();// ����ʂ̃f�[�^��S�č폜

		InputKey();

		//InputJoypad();

		scenemanager.execute();

		ScreenFlip();

	}

	ImGui_ImplDxLib_Shutdown();

	DxLib_End();                                            // �c�w���C�u�����g�p�̏I������
	return 0;                                               // �\�t�g�̏I��
}


LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplDxLib_WndProcHandler(wnd, msg, wParam, lParam)) {
		SetUseHookWinProcReturnValue(TRUE);
		return 1;
	}

	//IME�֘A��OS�ɔC����
	switch (msg)
	{
		//WM_IME_SETCONTEXT���󂯎�����Ƃ���
		//lParam = 0;�Ƃ����IME�֘A�̕\�����s���Ȃ��Ȃ�܂��B
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
