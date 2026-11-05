#pragma once
#include "../Object/objectBase.h"
#include "vector"

class MotionManager:public ObjectBase
{
public:
	MotionManager(const int& model);
	~MotionManager();
	void Update()override;
	void Play(const int& motionIndex, const int& _motionData,const float& _motionSpeed, const bool& _isLoop);
	
private:
	//モデルの設定
	int playingModel;
	//再生したいモーション
	int nowPlayMotion;
	float motionSpeed;
	float motionTime;
	//モーションの番号
	int currentMotion;
	//モーションをループするか
	bool isLoop;

	bool isMotionEnd;
	float motionEndTime;
};
