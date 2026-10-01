#pragma once
#include "objectBase.h"

/// <summary>
/// ボーナス中のステージ
/// 一定枚数払い出すと終了
/// </summary>
class FeverStage :public ObjectBase
{
public:
	FeverStage();
	~FeverStage();
	void Update()override;
	void Draw()override {};

private:

};

