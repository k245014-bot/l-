#include "CharacterBase.h"
//#include "../Common/Motion/MotionManager.h"

CharacterBase::CharacterBase()
{
	
}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Update()
{

}

void CharacterBase::Draw()
{
}

void CharacterBase::LoadModel(const std::string& _hModelName)
{
	std::string name = "data/model/" + _hModelName;
	hModel = MV1LoadModel(name.c_str());
}

void CharacterBase::SetAnimation(const int _motionId, const std::string& _playMotionName, const float& _motionSpeed, const bool& _isMotionLoop)
{
	motionId = _motionId;
	playMotion = MV1LoadModel(_playMotionName.c_str());
	motionSpeed = _motionSpeed;
	isMotionLoop = _isMotionLoop;
}
