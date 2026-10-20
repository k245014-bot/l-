#include "PlayScene.h"

#include "Sub/SubA/SubAManager.h"
#include "main/mainControl.h"
#include "main/flagLottery.h"
#include "Common/CameraEditor/CameraEditor.h"
#include "Common/Input/inputManager.h"

PlayScene::PlayScene()
{
	new InputManager;
	new SubAManager;

	new MainControl;

	flag = new FlagLottery;

	cameraEditor = nullptr;
	num = -1;
	hImage = 0;
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

	if (CheckHitKey(KEY_INPUT_LSHIFT) && CheckHitKey(KEY_INPUT_1))
	{
		if (cameraEditor == nullptr)
			cameraEditor = new CameraEditor;
	}

	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
		SceneManager::Exit();
	}
}

void PlayScene::Draw()
{
	//DrawGraph(0, 0, housingImage, true);
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	
	DrawFormatString(0, 100, GetColor(255, 255, 255), "% d", num);
}
