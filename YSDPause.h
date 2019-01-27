#pragma once
//////////////////////////////////////////////////////////
////
////			Pause.h
////
//////////////////////////////////////////////////////////

class PauseClass
{
private:


public:
	bool pauseState;
	int chosenItem;//‘I‘ğ’†‚Ì€–Ú
	int timer;

	void Init();
	void Update();
	void draw();
	void PauseMode_On();
	void PauseMode_Off();
	bool Get_PauseState();
};

extern PauseClass pause;
extern int pauseKey;






