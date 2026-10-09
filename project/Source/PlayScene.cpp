#include "PlayScene.h"
#include "main/flagLottery.h"

PlayScene::PlayScene()
{
	flag = new FlagLottery();
	num = -1;
}

PlayScene::~PlayScene()
{
	delete flag;
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		flag->SetRand();
		num = flag->GetSymbol();
	}

	if (CheckHitKey(KEY_INPUT_1))
	{
		flag->Reset();
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));


	DrawFormatString(0, 100, GetColor(255, 255, 255), "% d", num);
}
