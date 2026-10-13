#include "CameraManager.h"
#include "Camera.h"
#include "../Character/Mao/Mao.h"
#include "../Stage/Stage.h"

CameraManager::CameraManager()
{
	camera = new Camera;
    mao = FindGameObject<Mao>();
    stage = FindGameObject<Stage>();
    camera->Set(mao);
    m_3DTarget = MakeScreen(660 , 560, TRUE);
}

CameraManager::~CameraManager()
{
    DeleteGraph(m_3DTarget);
}

void CameraManager::Update()
{
    
}

void CameraManager::Draw()
{
    
}

void CameraManager::CameraDrawScreen()
{
    //2Dの筐体を通常画面に描画
    SetDrawScreen(DX_SCREEN_BACK);

    //3D演出を専用画面に描画
    SetDrawScreen(m_3DTarget);

    ClearDrawScreen();

    //カメラなどをここで呼ばないと座標が取得できないため
    camera->CameraMove();
    mao->ObjectDraw();
    stage->ObjectDraw();

    //通常画面に戻す
    SetDrawScreen(DX_SCREEN_BACK);

    //筐体の液晶部分に3D演出を重ねる
    DrawGraph(110, 255, m_3DTarget, TRUE);
}
