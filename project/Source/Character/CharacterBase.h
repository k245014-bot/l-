#pragma once
#include "../Common/Object/object3D.h"
#include "../Common/Animation/AnimationManager.h"

class AnimationManager;

class CharacterBase : public Object3D
{
public:
	CharacterBase();
	~CharacterBase();

	virtual void Update()override;
	virtual void Draw()override;

	const VECTOR3 GetPositon() { return data.position; }
protected:
	AnimationManager* animation;

	//data/model/以降のファイル名を入れる
	void LoadModel(const std::string& _hModelName);
	/// <summary>
	/// アニメーションのロードをする
	/// </summary>
	/// <param name="_anim">アニメーションを入れる変数</param>
	/// <param name="_playAnimName">ファイルの場所を指定</param>
	void LoadAnim(int& _anim, const std::string& _playAnimName);
	/// <summary>
	/// これでアニメーションを切り替える
	/// </summary>
	/// <param name="_motionId">同じものを再生しないようにするため</param>
	/// <param name="_animData">モーションのデータ</param>
	/// <param name="_motionSpeed">速度調整</param>
	/// <param name="_isMotionLoop">モーションをループするかどうか</param>
	void SetAnimation(const int _motionId, const int& _animData, const float& _motionSpeed, const bool& _isMotionLoop);

	int motionId;
	int playMotion;
	float motionSpeed;
	bool isMotionLoop;
};