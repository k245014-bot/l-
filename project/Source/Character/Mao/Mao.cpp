#include "Mao.h"

Mao::Mao()
{
	LoadModel(fileName);
	data.position = VZero;
	animation = new AnimationManager(hModel);
	SetAnimation(0, "data/model/mao/Motion/Dance.mv1", 30.0f, true);
}

Mao::~Mao()
{
}

void Mao::Update()
{
	animation->Play(motionId, playMotion, motionSpeed, isMotionLoop);
}

void Mao::Draw()
{

}