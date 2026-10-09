#include "SubBManager.h"
#include "../../Camera/Camera.h"
#include "../../Character/Mao/Mao.h"

SubBManager::SubBManager()
{
	mao = new Mao;
	camera = new Camera;

    camera->Set(mao);
    m_3DTarget = MakeScreen(800, 450, TRUE);
    housingImage = LoadGraph("data/texture/Sammy_Heiwa_kali.png");
}

SubBManager::~SubBManager()
{
    DeleteGraph(m_3DTarget);

    //delete mao;
    //delete camera;
}

void SubBManager::Update()
{
	CameraSet();
}

void SubBManager::Draw()
{
    // ‡@ 2D‚Ìâž‘Ì‚ð’Êí‰æ–Ê‚É•`‰æ
    SetDrawScreen(DX_SCREEN_BACK);

    DrawGraph(0, 0, housingImage, true);

    // ‡A 3D‰‰o‚ðê—p‰æ–Ê‚É•`‰æ
    SetDrawScreen(m_3DTarget);

    ClearDrawScreen();

    CameraSet();

    mao->ObjectDraw();

    // ‡B ’Êí‰æ–Ê‚É–ß‚·
    SetDrawScreen(DX_SCREEN_BACK);

    // ‡C âž‘Ì‚Ì‰t»•”•ª‚É3D‰‰o‚ðd‚Ë‚é
    DrawGraph(120, 175, m_3DTarget, TRUE);
}

void SubBManager::CameraSet()
{
    camera->Update();
}
