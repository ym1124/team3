#include"DxLib.h"
#include "scene.h"
#include <stdlib.h>
#include <time.h>

scene sc;
//TODO

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)

{

	SetMainWindowText("test");

	ChangeWindowMode(true);

	SetGraphMode(900, 700, 32);

	DxLib_Init();

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() != -1)
	{
		srand((unsigned int)(time(NULL)));
		ClearDrawScreen();

		sc.sceneManager();
		InputKey();

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}