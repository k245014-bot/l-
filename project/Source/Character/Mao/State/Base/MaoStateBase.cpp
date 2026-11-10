#include "MaoStateBase.h"
#include "../../Mao.h"

MaoStateBase::MaoStateBase()
{
	mao = FindGameObject<Mao>();
}

MaoStateBase::~MaoStateBase()
{
}

void MaoStateBase::Update()
{
}

void MaoStateBase::Draw()
{
}

void MaoStateBase::Start()
{
}

void MaoStateBase::Finish()
{
}
