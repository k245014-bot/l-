#include "MaoDanceAtkState.h"
#include "../Mao.h"

MaoDanceAtkState::MaoDanceAtkState()
{
}

MaoDanceAtkState::~MaoDanceAtkState()
{
}

void MaoDanceAtkState::Update()
{
}

void MaoDanceAtkState::Draw()
{
}

void MaoDanceAtkState::Start()
{
	mao->SetAnimation(1, mao->animData.attack, 40.0f, false);
}

void MaoDanceAtkState::Finish()
{
}
