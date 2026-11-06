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

void CharacterBase::LoadAnim(int& _anim, const std::string& _playAnimName)
{
	_anim = MV1LoadModel(_playAnimName.c_str());
}

void CharacterBase::SetAnimation(const int _motionId, const int& _animData, const float& _motionSpeed, const bool& _isMotionLoop)
{
	motionId = _motionId;
	playMotion = _animData;
	motionSpeed = _motionSpeed;
	isMotionLoop = _isMotionLoop;
}
