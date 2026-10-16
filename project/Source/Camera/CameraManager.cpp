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

void CameraManager::DrawObjects()
{
    mao->ObjectDraw();
    stage->ObjectDraw();
}
