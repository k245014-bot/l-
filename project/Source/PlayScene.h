#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>

class  FlagLottery2;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:

	FlagLottery2* flag;

	int hImage;
	//筐体の画像
	int housingImage;
	int num;

};
