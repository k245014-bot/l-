#include "BootScene.h"
#include "SoundManager.h"

BootScene::BootScene()
{
	/*SoundManager* sound = new SoundManager();
	sound->DontDestroyOnSceneChange();*/
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TITLE"); // ‹N“®‚ªI‚í‚Á‚½‚çTitle‚ğ•\¦
}

void BootScene::Draw()
{
}
