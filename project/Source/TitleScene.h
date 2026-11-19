#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
	
private:
	int button = 0;
	int random = 0;
	int result = 0;
	int battleResult = 0;
	int makon = 0;
	int stop = 0;
};
