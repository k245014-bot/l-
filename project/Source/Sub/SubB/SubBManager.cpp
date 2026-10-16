#include "SubBManager.h"
#include "../../Camera/Camera.h"
#include "Screen/ScreenManager.h"
#include "../../Character/Mao/Mao.h"
#include "../../Stage/Stage.h"

SubBManager::SubBManager()
{
	mao = new Mao;
    new Stage;
    cameraManager = new ScreenManager;
    housingImage = LoadGraph("data/texture/Sammy_Heiwa_ver1.0.png");
}

SubBManager::~SubBManager()
{
    DeleteGraph(housingImage);
}

void SubBManager::Update()
{
}

void SubBManager::Draw()
{
    cameraManager->CameraDrawScreen();
    DrawGraph(0, 0, housingImage, true);
}
