#pragma once
#include "../Object/objectBase.h"
#include "MotionId/MotionId.h"
#include "vector"

class MotionManager 
{
public:
	MotionManager();
	MotionManager(int& model);
	~MotionManager();

	void Play(int motionData);
	/// <summary>
	/// 再生
	/// </summary>
	/// <param name="speed">再生スピード</param>
	void Play(const float& speed = 0.4f);
	
	/// <summary>
	/// インプレイスじゃない再生
	/// </summary>
	/// <param name="rot">回転行列</param>
	/// <param name="speed">再生スピード</param>
	void Play(const MATRIX& rot, const float& speed = 0.4f);

	/// <summary>
	/// インプレイスじゃない再生(移動量調整できる)
	/// </summary>
	/// <param name="rot">回転行列</param>
	/// <param name="speed">再生スピード</param>
	void Play(const MATRIX& rot, const float& movement, const float& speed);

	/// <summary>
	///  指定の時間だけを再生
	/// </summary>
	/// <param name="rot">回転行列</param>
	/// <param name="startTime">開始時間(2週目から適応)</param>
	/// <param name="endTime">終了時間</param>
	/// <param name="speed">再生速度</param>
	/// <param name="loop">繰り返すか否か。使いたい場合のみtrueを入れる、使わないなら何も書かなくてもよい</param>
	void Play(const MATRIX& rot, const float& startTime, const float& endTime, const float& speed, const float& loop = false);

	
	void ChargeMove(const float& radiusX, const float& radiusZ, const float& speed, const int& index);

	void ChargeMove(VECTOR& pos, const float& radiusX, const float& radiusZ, const float& speed, const int& index);

	void ChargeSet(const bool& set);

	//ゲッター
	//VECTOR GetMotionVec() const { return playingPosition; }
	///*int GetNowTime()const { return motionNowData.nowTime; }
	//int GetMaxTime()const { return motionNowData.maxTime; }*/
	//int GetChangeMaxTime()const { return changeMaxTime; }
	//int GetMotionID() const { return playingID; }
	////bool GetReversCheck()const { return reversCheck[playingID]; }
	////セッター
	////void SetModel(const int& _model);
	//inline void SetPosition(const VECTOR& pos) { playingPosition = pos; }

	//inline void SetKeepResource(bool settingData) { keepResource = settingData; }

private:
	int playingModel;
	int nawPlayMotion;
	float motionSpeed;

	/*int playingID;
	VECTOR playingPosition;
	float playSpeed;
	float changeSpeed;
	float changeRate;
	
	int motionFlameIndex;
	VECTOR nowPosition;
	VECTOR prevPosition;

	bool keepResource;

	float vibrationAngle;
	bool charageCheck;

	float changeMaxTime;*/
};
