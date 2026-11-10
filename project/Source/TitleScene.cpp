#include "TitleScene.h"

extern "C" unsigned int GetRandom();

extern "C" int MakonLottery();

extern "C" int GetSlotButtons();

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
	if (CheckHitKey(KEY_INPUT_R))
	{
		random = GetRandom();
	}
	if (buttons & 2)
	{
		result = MakonLottery();
	}
}


void TitleScene::Draw()
{
	extern const char* Version();
	DrawString(0, 20, Version(), GetColor(255,255,255));
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawFormatString(
		100, 100,
		GetColor(255, 255, 255),
		"Random: %u",
		random
	);
	if (result == 1)
	{
		DrawString(100, 150, "魔魂当選！", GetColor(255, 255, 0));
	}
	else
	{
		DrawString(100, 150, "ハズレ", GetColor(255, 255, 255));
	}
}
