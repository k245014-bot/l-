#include "motionManager.h"
//#include "../Library/gameObject.h"
//#include "object3D.h"

//MotionManager::MotionManager()
//{
//	playingModel = -1;
//	nawPlayMotion = -1;
//	motionSpeed = 0;
//}

MotionManager::MotionManager(const int& model)
{
    playingModel = model;
	nowPlayMotion = -1;
	motionSpeed = 0;
	motionTime = 0;
    currentMotion = -1;
    isLoop = false;
    isMotionEnd = false;
    motionEndTime = 0;
}

MotionManager::~MotionManager()
{
	MV1DeleteModel(playingModel);
}

void MotionManager::Update()
{
    if(nowPlayMotion == -1) 
        return;

    if (isMotionEnd) 
        return;

    motionTime += Time::DeltaTime() * motionSpeed;

    // モーション終了判定
    if (motionTime >= motionEndTime)
    {
        if (isLoop)
        {
            // 再生時間を最初に戻す
            motionTime = fmodf(motionTime, motionEndTime);
        }
        else
        {
            motionTime = motionEndTime;
            isMotionEnd = true;
        }
    }

    MV1SetAttachAnimTime(playingModel, nowPlayMotion, motionTime);
}

void MotionManager::Play(const int& motionIndex, const int& _motionData, const float& _motionSpeed,const bool& _isLoop)
{
    // 同じモーションなら再設定しない
    if (currentMotion == motionIndex)
    {
        return;
    }

    // 前のモーションを解除
    if (nowPlayMotion != -1)
    {
        MV1DetachAnim(playingModel, nowPlayMotion);
    }

    nowPlayMotion = MV1AttachAnim(playingModel, motionIndex, _motionData, true);

    if (nowPlayMotion == -1) 
        return;

    currentMotion = motionIndex;

    motionSpeed = _motionSpeed;
    isLoop = _isLoop;

    motionTime = 0.0f;
    isMotionEnd = false;

    motionEndTime = MV1GetAttachAnimTotalTime(playingModel, nowPlayMotion);
}
