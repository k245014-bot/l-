#include "motionManager.h"
//#include "../Library/gameObject.h"
//#include "object3D.h"

MotionManager::MotionManager()
{
	playingModel = -1;
	nawPlayMotion = -1;
	motionSpeed = 0;
}

MotionManager::MotionManager(int& model)
{
	MotionManager();
	playingModel = model;
	/*playingID = -1;
	playSpeed = 0;

	changeRate = 0;
	changeSpeed = 0;

	motionFlameIndex = 0;
	playingPosition = VGet(0, 0, 0);
	nowPosition = VGet(0, 0, 0);
	prevPosition = VGet(0, 0, 0);

	keepResource = false;

	charageCheck = false;
	changeMaxTime = 0;
	vibrationAngle = 0;*/
}

MotionManager::~MotionManager()
{
	
}

void MotionManager::Play(int motionData)
{
	if (nawPlayMotion != -1)
	{
		MV1DetachAnim(playingModel, nawPlayMotion);
		nawPlayMotion = -1;
	}

	// モーションを設定
	nawPlayMotion = MV1AttachAnim(playingModel, motionData);

	// 再生速度を設定
	this->motionSpeed = motionSpeed;

	// 再生時間を初期化
	motionSpeed = 0.0f;

	// 再生開始位置
	MV1SetAttachAnimTime(playingModel, nawPlayMotion, motionSpeed);
}

//通常の再生処理
//void MotionManager::Play(const float& speed)
//{
//	//逆再生かどうか
//	if (reversCheck[playingID] == false)
//	{
//		//アタッチしている場合
//		if (motionNowData.attachID >= 0)
//		{
//			motionNowData.nowTime += speed;
//
//			//再生時間が最大まで行ったとき
//			if (motionNowData.nowTime >= motionNowData.maxTime)
//			{
//
//				if (loopCheck[playingID] == true)
//				{
//					//再生時間をリセット
//					motionNowData.nowTime -= motionNowData.maxTime;
//				}
//				else
//				{
//					motionNowData.nowTime = motionNowData.maxTime;
//				}
//
//			}
//			MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//
//		}
//
//		if (motionPrevData.attachID >= 0)
//		{
//			//変更するフレームに倍率が合うように割る
//			changeRate += 1.0f / changeSpeed;
//			if (changeRate >= 1.0f)
//			{
//				changeRate = 1.0f;
//				changeSpeed = 0;
//				//前のモーションをデタッチする
//				MV1DetachAnim(playingModel, motionPrevData.attachID);
//				//今のモーションの変更率を100%にする
//				MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, 1.0f);
//
//				//これ以上処理に入らないように初期化する
//				motionPrevData.attachID = -1;
//			}
//			else
//			{
//				//変更が終わってない場合変更率に合わせてブレンドする
//
//				//今のモーションを徐々に適応させる
//				MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, changeRate);
//				//今のモーションを徐々に消してく
//				MV1SetAttachAnimBlendRate(playingModel, motionPrevData.attachID, 1.0f - changeRate);
//			}
//		}
//	}
//	else
//	{
//
//		if (motionNowData.attachID >= 0)
//		{
//			motionNowData.nowTime -= speed;
//
//			if (motionNowData.nowTime <= 0)
//			{
//
//				if (loopCheck[playingID] == true)
//				{
//					//再生時間をリセット
//					motionNowData.nowTime = motionNowData.maxTime;
//				}
//				else
//				{
//					motionNowData.nowTime += motionNowData.maxTime;
//				}
//
//			}
//			
//			MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//		}
//
//		if (motionPrevData.attachID >= 0)
//		{
//
//			//変更するフレームに倍率が合うように割る
//			changeRate += 1.0f / changeSpeed;
//			if (changeRate >= 1.0f)
//			{
//				changeRate = 1.0f;
//				changeSpeed = 0;
//				//前のモーションをデタッチする
//				MV1DetachAnim(playingModel, motionPrevData.attachID);
//				//今のモーションの変更率を100%にする
//				MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, 1.0f);
//
//				//これ以上処理に入らないように初期化する
//				motionPrevData.attachID = -1;
//			}
//			else
//			{
//
//				//motionPrevData.nowTime = 33.0f;
//
//				//変更が終わってない場合変更率に合わせてブレンドする
//
//				//今のモーションを徐々に適応させる
//				MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, changeRate);
//				//今のモーションを徐々に消してく
//				MV1SetAttachAnimBlendRate(playingModel, motionPrevData.attachID, 1.0f - changeRate);
//			}
//
//			
//		}
//	}
//}

//インプレースじゃないモデルの再生処理
//void MotionManager::Play(const MATRIX& rot, const float& speed)
//{
//	if (motionNowData.attachID >= 0)
//	{
//		// アニメーション時間を進める前の『アニメーションで移動をしているフレームの座標』を取得しておく
//		// モデルの向きによって進み方を変えれるようにVTransformで回転行列と合わせる
//		prevPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//
//		motionNowData.nowTime += speed;
//
//		if (motionNowData.nowTime >= motionNowData.maxTime)
//		{
//			MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.maxTime);
//			//新しいモーション再生時間での移動をしているフレームの座標を取得
//			nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex),rot);
//			//モーションを進める前の座標とモーションの終わりに際の座標の差分を代入
//			playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//
//			if (loopCheck[playingID] == true)
//			{
//				//再生時間をリセット
//				motionNowData.nowTime -= motionNowData.maxTime;
//
//				MV1SetAttachAnimTime(playingModel, motionNowData.attachID, 0.0f);
//				//アニメーション時間を進める前の『アニメーションで移動をしているフレームの座標』を取得しておく
//				prevPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex),rot);
//
//				MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//				//新しいモーション再生時間での移動をしているフレームの座標を取得
//				nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex),rot);
//
//				//再生される前のモーションを差分を代入する
//				playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//			}
//			else
//			{
//				motionNowData.nowTime = motionNowData.maxTime;
//			}
//
//		}
//		else
//		{
//			MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//
//			//新しいモーション再生時間での移動をしているフレームの座標を取得
//			nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//			//再生される前のモーションを差分を代入する
//			playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//		}
//
//	}
//
//	if (motionPrevData.attachID >= 0)
//	{
//		//変更するフレームに倍率が合うように割る
//		changeRate += 1.0f / changeSpeed;
//		if (changeRate >= 1.0f)
//		{
//			changeRate = 1.0f;
//			changeSpeed = 0;
//			//前のモーションをデタッチする
//			MV1DetachAnim(playingModel, motionPrevData.attachID);
//			//今のモーションの変更率を100%にする
//			MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, 1.0f);
//
//			//これ以上処理に入らないように初期化する
//			motionPrevData.attachID = -1;
//		}
//		else
//		{
//			//変更が終わってない場合変更率に合わせてブレンドする
//
//			//今のモーションを徐々に適応させる
//			MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, changeRate);
//			//今のモーションを徐々に消してく
//			MV1SetAttachAnimBlendRate(playingModel, motionPrevData.attachID, 1.0f - changeRate);
//		}
//	}
//
//}

//void MotionManager::Play(const MATRIX& rot, const float& movement, const float& speed)
//{
//	if (motionNowData.attachID >= 0)
//	{
//		// アニメーション時間を進める前の『アニメーションで移動をしているフレームの座標』を取得しておく
//		// モデルの向きによって進み方を変えれるようにVTransformで回転行列と合わせる
//		prevPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//
//		//prevPosition = VAdd(prevPosition, VTransform(VGet(0.0f, 0.0f, movement), rot));
//
//		motionNowData.nowTime += speed;
//
//		if (motionNowData.nowTime >= motionNowData.maxTime)
//		{
//			MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.maxTime);
//			//新しいモーション再生時間での移動をしているフレームの座標を取得
//			nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//			
//			nowPosition = VAdd(nowPosition, VTransform(VGet(0.0f, 0.0f, movement), rot));
//			
//			//モーションを進める前の座標とモーションの終わりに際の座標の差分を代入
//			playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//
//			if (loopCheck[playingID] == true)
//			{
//				//再生時間をリセット
//				motionNowData.nowTime -= motionNowData.maxTime;
//
//				MV1SetAttachAnimTime(playingModel, motionNowData.attachID, 0.0f);
//				//アニメーション時間を進める前の『アニメーションで移動をしているフレームの座標』を取得しておく
//				prevPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//
//				//prevPosition = VAdd(prevPosition, VTransform(VGet(0.0f, 0.0f, movement), rot));
//
//				MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//				//新しいモーション再生時間での移動をしているフレームの座標を取得
//				nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//
//				//再生される前のモーションを差分を代入する
//				playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//			}
//			else
//			{
//				motionNowData.nowTime = motionNowData.maxTime;
//			}
//
//		}
//		else
//		{
//			MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//
//			//新しいモーション再生時間での移動をしているフレームの座標を取得
//			nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//			
//			nowPosition = VAdd(nowPosition, VTransform(VGet(0.0f, 0.0f, movement), rot));
//
//			//再生される前のモーションを差分を代入する
//			playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//		}
//
//	}
//
//	if (motionPrevData.attachID >= 0)
//	{
//		//変更するフレームに倍率が合うように割る
//		changeRate += 1.0f / changeSpeed;
//		if (changeRate >= 1.0f)
//		{
//			changeRate = 1.0f;
//			changeSpeed = 0;
//			//前のモーションをデタッチする
//			MV1DetachAnim(playingModel, motionPrevData.attachID);
//			//今のモーションの変更率を100%にする
//			MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, 1.0f);
//
//			//これ以上処理に入らないように初期化する
//			motionPrevData.attachID = -1;
//		}
//		else
//		{
//			//変更が終わってない場合変更率に合わせてブレンドする
//
//			//今のモーションを徐々に適応させる
//			MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, changeRate);
//			//今のモーションを徐々に消してく
//			MV1SetAttachAnimBlendRate(playingModel, motionPrevData.attachID, 1.0f - changeRate);
//		}
//	}
//}

//void MotionManager::Play(const MATRIX& rot, const float& startTime, const float& endTime, const float& speed, const float& loop)
//{
//	changeMaxTime = endTime;
//
//	if (motionNowData.attachID >= 0)
//	{
//		// アニメーション時間を進める前の『アニメーションで移動をしているフレームの座標』を取得しておく
//		// モデルの向きによって進み方を変えれるようにVTransformで回転行列と合わせる
//		prevPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//
//		if (charageCheck == false)
//		{
//			motionNowData.nowTime += speed;
//		}
//	
//		if (motionNowData.nowTime >= changeMaxTime)
//		{
//			charageCheck = true;
//
//			if (loop == true)
//			{
//				MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.maxTime);
//				//新しいモーション再生時間での移動をしているフレームの座標を取得
//				nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//				//モーションを進める前の座標とモーションの終わりに際の座標の差分を代入
//				playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//
//				//再生時間をリセット
//				motionNowData.nowTime -= motionNowData.maxTime;
//
//				motionNowData.nowTime = startTime;
//
//				MV1SetAttachAnimTime(playingModel, motionNowData.attachID, 0.0f);
//				//アニメーション時間を進める前の『アニメーションで移動をしているフレームの座標』を取得しておく
//				prevPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//
//				MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//				//新しいモーション再生時間での移動をしているフレームの座標を取得
//				nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//
//				//再生される前のモーションを差分を代入する
//				playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//			}
//			else
//			{
//				MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//
//				//新しいモーション再生時間での移動をしているフレームの座標を取得
//				nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//				//再生される前のモーションを差分を代入する
//				playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//			}
//
//		}
//		else
//		{
//			MV1SetAttachAnimTime(playingModel, motionNowData.attachID, motionNowData.nowTime);
//
//			//新しいモーション再生時間での移動をしているフレームの座標を取得
//			nowPosition = VTransform(MV1GetAttachAnimFrameLocalPosition(playingModel, motionNowData.attachID, motionFlameIndex), rot);
//
//			//再生される前のモーションを差分を代入する
//			playingPosition = VAdd(playingPosition, VScale(VSub(nowPosition, prevPosition), 1.0f));
//		}
//		
//
//	}
//
//	if (motionPrevData.attachID >= 0)
//	{
//		//変更するフレームに倍率が合うように割る
//		changeRate += 1.0f / changeSpeed;
//		if (changeRate >= 1.0f)
//		{
//			changeRate = 1.0f;
//			changeSpeed = 0;
//			//前のモーションをデタッチする
//			MV1DetachAnim(playingModel, motionPrevData.attachID);
//			//今のモーションの変更率を100%にする
//			MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, 1.0f);
//
//			//これ以上処理に入らないように初期化する
//			motionPrevData.attachID = -1;
//		}
//		else
//		{
//			//変更が終わってない場合変更率に合わせてブレンドする
//
//			//今のモーションを徐々に適応させる
//			MV1SetAttachAnimBlendRate(playingModel, motionNowData.attachID, changeRate);
//			//今のモーションを徐々に消してく
//			MV1SetAttachAnimBlendRate(playingModel, motionPrevData.attachID, 1.0f - changeRate);
//		}
//	}
//}

//void MotionManager::ChargeMove(const float& radiusX, const float& radiusZ, const float& speed, const int& index)
//{
//	if (charageCheck == false)
//	{
//		return;
//	}
//
//	playingPosition.x = playingPosition.x - (float)sin(vibrationAngle) * radiusX;
//	playingPosition.z = playingPosition.z - (float)cos(vibrationAngle) * radiusZ;
//	vibrationAngle += speed;
//
//}
//
//void MotionManager::ChargeMove(VECTOR& pos, const float& radiusX, const float& radiusZ, const float& speed, const int& index)
//{
//	if (charageCheck == false)
//	{
//		return;
//	}
//
//
//	playingPosition.x = playingPosition.x - (float)sin(vibrationAngle) * radiusX;
//	playingPosition.z = playingPosition.z - (float)cos(vibrationAngle) * radiusZ;
//	vibrationAngle += speed;
//}
//
//void MotionManager::ChargeSet(const bool& set)
//{
//	charageCheck = set;
//}

/*
void MotionManager::ChargeAngleSet(const int& num)
{
	for (int i = 0; i < num; i++)
	{
		vibrationAngle.emplace_back();
	}
}
*/