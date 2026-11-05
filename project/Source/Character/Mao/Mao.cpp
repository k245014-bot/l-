#include "Mao.h"

Mao::Mao()
{
	hModel = MV1LoadModel("data/model/mao/mao2.mv1");
	data.position = VZero;
	motionManager = new MotionManager(hModel);

	MotionLoad(0, "data/model/mao/Motion/Dance.mv1", 30.0f, true);
}

Mao::~Mao()
{
}

void Mao::Update()
{
	motionManager->Play(motionId, playMotion, motionSpeed, isMotionLoop);
}

void Mao::Draw()
{

}