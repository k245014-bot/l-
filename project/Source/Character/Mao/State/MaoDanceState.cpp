#include "MaoDanceState.h"
#include "../Mao.h"

MaoDanceState::MaoDanceState()
{
	//mao = FindGameObject<Mao>();
}

MaoDanceState::~MaoDanceState()
{
}

void MaoDanceState::Update()
{
}

void MaoDanceState::Draw()
{
}

void MaoDanceState::Start()
{
	mao->SetAnimation(0, mao->animData.dance, 30.0f, true);
}

void MaoDanceState::Finish()
{
}
