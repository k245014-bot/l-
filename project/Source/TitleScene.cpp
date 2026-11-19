#include "TitleScene.h"

extern "C"
{
	unsigned int GetRandom();

	int MakonLottery();

	int GetSlotButtons();

	int MakonControl(int type);

	int MakonBattle();

	int GetMakon();

	void ResetMakon();

}
TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	int buttons = GetSlotButtons();
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}

	//---------------------------------------------------------------------------

	makon = GetMakon();

	if (CheckHitKey(KEY_INPUT_R))
	{
		random = GetRandom();
	}

	if (buttons & 2)
	{
		result = MakonLottery();
		if (result == 1)
		{
			MakonControl(0);
		}
	}

	

	if (buttons & 1)
	{
		battleResult = MakonBattle();
	}

	if (battleResult == -1)
	{
		ResetMakon();
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawFormatString(100, 100,GetColor(255, 255, 255),"Random: %u",random);
	DrawFormatString(100, 200, GetColor(255, 255, 0), "Makon: %u", makon);
	if (result == 1)
	{
		DrawString(100, 150, "魔魂当選！", GetColor(255, 255, 0));
	}
	else
	{
		DrawString(100, 150, "ハズレ", GetColor(255, 255, 255));
	}

	if (battleResult == 1)
	{
		DrawString(100, 350, "勝利！", GetColor(255, 0, 0));
	}
	else if (battleResult == 0)
	{
		DrawString(100, 350, "敗北！", GetColor(0, 255, 0));
	}
}
