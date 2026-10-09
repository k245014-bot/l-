#include "SubBManager.h"
#include "../../Camera/Camera.h"
#include "../../Character/Mao/Mao.h"

SubBManager::SubBManager()
{
	mao = new Mao;
	camera = new Camera;

    camera->Set(mao);
    m_3DTarget = MakeScreen(800, 450, TRUE);
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
    // ‡@ 3D‰‰o—p‚Ì‰æ–Ê‚ÉØ‚è‘Ö‚¦‚é
    SetDrawScreen(m_3DTarget);

    ClearDrawScreen();

    // ‡A ‚±‚±‚Å3D‚ð•`‰æ
    CameraSet();

    mao->Draw();

    // ‡B ’Êí‚Ì‰æ–Ê‚É–ß‚·
    SetDrawScreen(DX_SCREEN_BACK);

    // ‡C 3D‰æ–Ê‚ð2D‚Æ‚µ‚Ä“\‚è•t‚¯‚é
    DrawGraph(120, 175, m_3DTarget, TRUE);
}

void SubBManager::CameraSet()
{
    camera->Update();

}
