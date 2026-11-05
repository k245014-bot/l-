#pragma once
#include "../Object/objectBase.h"
#include "vector"

class AnimationManager:public ObjectBase
{
public:
	AnimationManager(const int& model);
	~AnimationManager();
	void Update()override;
	/// <summary>
	/// モーションを再生する
	/// </summary>
	/// <param name="motionIndex">同じIDだった場合アタッチしないようにする</param>
	/// <param name="_motionData">再生したいモーションのデータを入れる</param>
	/// <param name="_motionSpeed">モーションの再生速度の設定</param>
	/// <param name="_isLoop">モーションをループするかどうか</param>
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
