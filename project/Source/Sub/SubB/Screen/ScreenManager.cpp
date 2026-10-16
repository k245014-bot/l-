#include "ScreenManager.h"
#include "../../../Camera/Camera.h"
#include "../../../Character/Mao/Mao.h"
#include "../../../Stage/Stage.h"

ScreenManager::ScreenManager()
{
	camera = new Camera;
    mao = FindGameObject<Mao>();
    stage = FindGameObject<Stage>();
    camera->Set(mao);
    m_3DTarget = MakeScreen(660 , 560, TRUE);
}

ScreenManager::~ScreenManager()
{
    DeleteGraph(m_3DTarget);
}

void ScreenManager::Update()
{
    
}

void ScreenManager::Draw()
{
    
}

void ScreenManager::CameraDrawScreen()
{
    //2D‚Ìâž‘Ì‚ð’Êí‰æ–Ê‚É•`‰æ
    SetDrawScreen(DX_SCREEN_BACK);

    //3D‰‰o‚ðê—p‰æ–Ê‚É•`‰æ
    SetDrawScreen(m_3DTarget);

    ClearDrawScreen();

    //ƒJƒƒ‰‚È‚Ç‚ð‚±‚±‚ÅŒÄ‚Î‚È‚¢‚ÆÀ•W‚ªŽæ“¾‚Å‚«‚È‚¢‚½‚ß
    camera->CameraMove();
    DrawObjects();

    //’Êí‰æ–Ê‚É–ß‚·
    SetDrawScreen(DX_SCREEN_BACK);

    //âž‘Ì‚Ì‰t»•”•ª‚É3D‰‰o‚ðd‚Ë‚é
    DrawGraph(110, 255, m_3DTarget, TRUE);
}

void ScreenManager::DrawObjects()
{
    mao->ObjectDraw();
    stage->ObjectDraw();
}
