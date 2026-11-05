#pragma once
#include "../Common/Object/object3D.h"
#include "../Common/Motion/MotionManager.h"

class MotionManager;

class CharacterBase : public Object3D
{
public:
	CharacterBase();
	~CharacterBase();

	virtual void Update()override;
	virtual void Draw()override;

	const VECTOR3 GetPositon() { return data.position; }
protected:
	MotionManager* motionManager;
	void MotionLoad(const int _motionId, const std::string& _playMotionName, const float& _motionSpeed, const bool& _isMotionLoop);

	int motionId;
	int playMotion;
	float motionSpeed;
	bool isMotionLoop;
};